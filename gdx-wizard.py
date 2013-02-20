import os, sys
import argparse
import shutil
from subprocess import call
import multiprocessing

#
def write_template(origin_file, dest_dir, dest_name, **kwargs):
	template = open(origin_file + '.template').read().format(**kwargs)

	f = open(dest_dir + '/' + dest_name, 'w')
	f.write(template)
	f.close()

def cleanup_and_prepare(path, enforce=False):
	if os.path.exists(path):
		answer = raw_input(path + " already exists. Delete it? <y/N>:")
		
		if answer == 'y' or answer == 'Y':
			if enforce:
				answer = raw_input(path + " already exists, and is important.Are you REALLY sure?? <yes/Nope>:")
				if answer != 'yes':
					return False
			shutil.rmtree(path)
		else:
			os.chdir(path)
			return False

	os.mkdir(path)
	os.chdir(path)
	return True

def setup(): 
	parser = argparse.ArgumentParser(description='gdx++ project setup tool')
	parser.add_argument('--gen-mode', type=str, help="set's up the desired generation mode [android,linux,source,ios]")
	parser.add_argument('--root-dir', type=str, help="Defines the directory where the structure will be generated", required=True)
	parser.add_argument('--project-name', type=str, help="Defines the name of the project, the executable name and the android apk name", required=True)
	parser.add_argument('--android-sdk', type=str, help="The path to the android sdk")
	parser.add_argument('--android-ndk', type=str, help="The path to the android ndk")
	parser.add_argument('--package-name', type=str, help="The package name when generating Android/iOS deps")
	parser.add_argument('--android-target', type=str, help="The android target. ex: 'android-10'")

	args = parser.parse_args()
	args.gen_mode = args.gen_mode.split(',')

	gdx_source_dir = os.getcwd()

	root_path = os.path.abspath(os.path.expanduser(args.root_dir)) \
						+ '/'+ args.project_name.lower()

	if not os.path.exists(root_path):
		os.mkdir(root_path)
		os.mkdir(root_path + '/src')

	if not os.path.exists(root_path + '/src'):
		args.gen_mode.append('source')

	data_path = root_path + '/data'
	source_path = root_path + '/src/' + args.project_name
	gdx_source_path = root_path + '/gdx-cpp'

	if 'source' in args.gen_mode or not os.path.exists(source_path):
		cleanup_and_prepare(source_path, True)		
		cleanup_and_prepare(data_path)

		write_template(gdx_source_dir + '/template/CMakeLists.txt', root_path,
						'CMakeLists.txt',
						ProjectName = args.project_name )

		write_template(gdx_source_dir + '/template/main.cpp', source_path,
				   'main.cpp',
				   ProjectName = args.project_name )

		call(['cp', gdx_source_dir + '/etc/assets/data/logo.png', data_path])
		call(['ln', '-s', gdx_source_dir, gdx_source_path])

	if 'linux' in args.gen_mode:					
		project_path = root_path + '/linux/'

		if cleanup_and_prepare(project_path):		
			call(['cmake', '-DCMAKE_BUILD_TYPE=Release', root_path])
			call(['ln', '-s', data_path, 'bin/'])

	if 'android' in args.gen_mode:
		if not args.android_sdk:
			print 'Missing --android-sdk. Aborting'
			sys.exit(1)

		if not args.package_name:
			print 'Missing --package-name. Aborting'
			sys.exit(1)

		project_path = root_path + '/android'
		os.environ['ANDROID_NDK'] = args.android_ndk

		if not os.path.exists(root_path + '/src/java'):
			args.gen_mode.append('android-src')


		if cleanup_and_prepare(project_path):
			call(['cmake', '-DCMAKE_TOOLCHAIN_FILE=' + gdx_source_dir + '/cmake/android.toolchain.cmake',
			 	  root_path])
			del os.environ["ANDROID_NDK"]

	if 'android-src' in args.gen_mode:
		os.chdir(root_path)
		java_src_path = root_path + '/src/java'
		activity = args.project_name[0].upper() + args.project_name[1:] + 'Activity'

		if cleanup_and_prepare(java_src_path):
			call(args.android_sdk + '/tools/android create project --target ' + args.android_target + 
				' --path ' + java_src_path + ' --activity ' + activity + ' --package ' + args.package_name, shell=True)

			os.chdir(java_src_path)
			os.mkdir('libs/armeabi-v7a')
			os.mkdir('assets')

			call(['ln', '-s', root_path + '/android/lib/lib' + args.project_name + '.so', 'libs/armeabi-v7a' ])
			call(['ln', '-s', root_path + '/data', java_src_path + '/assets/data' ])

			write_template(gdx_source_dir + '/template/MainActivity.java', 
				root_path + '/src/java/src/' + args.package_name.replace('.','/'),
				activity + '.java', PackageName = args.package_name,
				ProjectName = args.project_name )

	if 'ios' in args.gen_mode:
		project_path = root_path + '/ios'

		if not os.path.exists(source_path + '/Info.plist'):
			write_template(gdx_source_dir + '/template/Info.plist', source_path, 'Info.plist', 
				PackageName = args.package_name)
		
		if not os.path.exists(source_path + '/bind.mm'):
			call(['cp', gdx_source_dir + '/template/bind.mm', source_path])
		
		if cleanup_and_prepare(project_path):
			call(['cmake','-GXcode', '-DCMAKE_TOOLCHAIN_FILE=' + gdx_source_dir + '/cmake/iOS.toolchain.cmake', root_path])

	if not args.gen_mode:
		print 'No target specified (--gen-mode). Exiting.'

if __name__ == "__main__": 
	setup()