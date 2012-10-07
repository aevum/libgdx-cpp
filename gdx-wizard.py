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

def cleanup(project_path):
	if os.path.exists(project_path):
		answer = raw_input(project_path + " already exists. Delete it? <y/N>:")
		if answer == 'y' or answer == 'Y':
			shutil.rmtree(project_path)
		else:
			print 'exiting.'
			sys.exit(1)

def gen_source(root_path, args):
	cleanup(root_path)
	os.mkdir(root_path)
	os.mkdir(root_path + '/src')
	os.mkdir(root_path + '/src/native')

	write_template('template/CMakeLists.txt', root_path + '/src/native',
					'CMakeLists.txt',
					ProjectName = args.project_name )

	write_template('template/main.cpp', root_path + '/src/native',
				   'main.cpp',
				   ProjectName = args.project_name )

def setup(): 
	parser = argparse.ArgumentParser(description='gdx++ project setup tool')
	parser.add_argument('--gen-mode', type=str, help="set's up the desired generation mode [android,linux,source,ios]")
	parser.add_argument('--root-dir', type=str, help="Defines the directory where the structure will be generated", required=True)
	parser.add_argument('--project-name', type=str, help="Defines the name of the project, the executable name and the android apk name", required=True)
	parser.add_argument('--android-ndk', type=str, help="The path to the android ndk")
	parser.add_argument('--android-sdk', type=str, help="The path to the android ndk")
	parser.add_argument('--package-name', type=str, help="The package name when generating Android/iOS deps")

	args = parser.parse_args()
	args.gen_mode = args.gen_mode.split(',')

	gdx_source_dir = os.getcwd()

	root_path = os.path.abspath(os.path.expanduser(args.root_dir)) \
						+ '/'+ args.project_name.lower()

	if not os.path.exists(root_path + '/src'):
		args.gen_mode.append('source')

	if 'source' in args.gen_mode:
		gen_source(root_path, args)

	if 'linux' in args.gen_mode:					
		project_path = root_path + '/linux/'
		project_build_path  = project_path + args.project_name
		gdx_build_path = project_path + '/gdx' 

		cleanup(project_path)
	
		os.mkdir(project_path)
		os.mkdir(project_build_path)
		os.mkdir(gdx_build_path)

		os.chdir(gdx_build_path)

		call(['cmake', '-DCMAKE_BUILD_TYPE=Release', gdx_source_dir ])
		call(['make', '-j' + str(multiprocessing.cpu_count())])
		
		os.chdir(project_build_path)

		call(['cmake', '-DGDX_SOURCE=' + gdx_source_dir,
			  '-DGDX_ROOT=' + gdx_build_path, root_path + '/src/native'])

	if 'android' in args.gen_mode:
		if not args.android_ndk:
			print 'Missing --android-ndk. Aborting'
			sys.exit(1)

		if not args.android_sdk:
			print 'Missing --android-sdk. Aborting'
			sys.exit(1)

		if not args.package_name:
			print 'Missing --package-name. Aborting'
			sys.exit(1)

		project_path = root_path + '/android/'
		gdx_build_path = project_path + '/gdx'
		project_build_path  = project_path + '/native/'

		if not os.path.exists(root_path + '/src/java'):
			args.gen_mode.append('android-src')

		cleanup(project_path)
	
		os.mkdir(project_path)
		os.mkdir(project_build_path)
		os.mkdir(gdx_build_path)

		os.chdir(gdx_build_path)

		os.environ['ANDROID_NDK'] = args.android_ndk
		os.environ['ANDROID_HOME'] = args.android_sdk

		call(['cmake', '-DCMAKE_BUILD_TYPE=Release', '-DCMAKE_TOOLCHAIN_FILE=' + gdx_source_dir + '/cmake/android.toolchain.cmake'
		 , '-DANDROID_NDK='+ args.android_ndk, gdx_source_dir ])
		
		call(['make', '-j' + str(multiprocessing.cpu_count())])

		os.chdir(project_build_path)

		call(['cmake', '-DGDX_SOURCE=' + gdx_source_dir, '-DCMAKE_TOOLCHAIN_FILE=' + gdx_source_dir + '/cmake/android.toolchain.cmake',
			  '-DGDX_ROOT=' + gdx_build_path, root_path + '/src/native'])

		call(['make', '-j' + str(multiprocessing.cpu_count())])


	if 'android-src' in args.gen_mode:
		os.chdir(root_path)
		java_src_path = root_path + '/src/java'

		cleanup(java_src_path)

		activity = args.project_name[0].upper() + args.project_name[1:] + 'Activity'

		call(['android', 'create', 'project', '--target', 'android-9', 
				'--path', java_src_path , '--activity', activity,
				'--package',  args.package_name])

		os.chdir(java_src_path)
		os.mkdir('libs/armeabi-v7a')

		call(['ln', '-s', root_path + '/android/native/lib/lib' + args.project_name + '.so', 'libs/armeabi-v7a' ])

		os.chdir(gdx_source_dir)

		write_template('template/MainActivity.java', 
			root_path + '/src/java/src/' + args.package_name.replace('.','/'),
			activity + '.java', PackageName = args.package_name,
			ProjectName = args.project_name )

	if not args.gen_mode:
		print 'No target specified (--gen-mode). Exiting.'


if __name__ == "__main__": 
	setup()