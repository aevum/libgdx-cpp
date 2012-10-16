import os, sys
import argparse
import shutil
from subprocess import call
import multiprocessing

#
def write_template(origin_file, dest_dir, dest_name, **kwargs):
	os.chdir(gdx_dir)
	template = open(origin_file + '.template').read().format(**kwargs)

	f = open(dest_dir + '/' + dest_name, 'w')
	f.write(template)
	f.close()

def cleanup_and_prepare(path, enforce=False):
	removed = False
	
	if os.path.exists(path):
		answer = raw_input(path + " already exists. Delete it? <y/N>:")
		
		if answer == 'y' or answer == 'Y':
			if enforce:
				answer = raw_input(path + " already exists, and is important.Are you REALLY sure?? <yes/Nope>:")
				if answer != 'yes':
					return False
			shutil.rmtree(path)
			removed = True
		else:
			os.chdir(path)
			return False

	os.mkdir(path)
	os.chdir(path)
	return removed

def setup(): 
	parser = argparse.ArgumentParser(description='gdx++ project setup tool')
	parser.add_argument('--gen-mode', type=str, help="set's up the desired generation mode [android,linux,source,ios]")
	parser.add_argument('--root-dir', type=str, help="Defines the directory where the structure will be generated", required=True)
	parser.add_argument('--project-name', type=str, help="Defines the name of the project, the executable name and the android apk name", required=True)
	parser.add_argument('--android-sdk', type=str, help="The path to the android sdk")
	parser.add_argument('--android-ndk', type=str, help="The path to the android ndk")
	parser.add_argument('--package-name', type=str, help="The package name when generating Android/iOS deps")
	parser.add_argument('--ios-sdk-ver', type=str, help="The sdk version in which the project will be built (ios 5.0 or later)")

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

	if 'source' in args.gen_mode or not os.path.exists(source_path):
		if cleanup_and_prepare(source_path, True):
			os.mkdir(source_path)
		
		if cleanup_and_prepare(data_path):
			os.mkdir(data_path)

		write_template(gdx_source_dir + '/template/CMakeLists.txt', source_path,
						'CMakeLists.txt',
						ProjectName = args.project_name )

		write_template(gdx_source_dir + '/template/main.cpp', source_path,
				   'main.cpp',
				   ProjectName = args.project_name )

		call(['cp', gdx_source_dir + '/etc/assets/data/logo.png', data_path])

	if 'linux' in args.gen_mode:					
		project_path = root_path + '/linux/'
		project_build_path  = project_path + args.project_name
		gdx_build_path = project_path + '/gdx' 

		if not os.path.exists(project_path):
			os.mkdir(project_path)

		if cleanup_and_prepare(gdx_build_path):		
			call(['cmake', '-DCMAKE_BUILD_TYPE=Release', gdx_source_dir ])

		call(['make', '-j' + str(multiprocessing.cpu_count())])

		if cleanup_and_prepare(project_build_path):		
			call(['cmake', '-DCMAKE_BUILD_TYPE=Release',
			  '-DGDX_SOURCE=' + gdx_source_dir,
			  '-DGDX_ROOT=' + gdx_build_path, root_path + '/src/' + args.project_name])

		call(['make', '-j' + str(multiprocessing.cpu_count())])
		call(['ln', '-s', data_path, '.'])

	if 'android' in args.gen_mode:
		if not args.android_sdk:
			print 'Missing --android-sdk. Aborting'
			sys.exit(1)

		if not args.package_name:
			print 'Missing --package-name. Aborting'
			sys.exit(1)

		project_path = root_path + '/android'
		gdx_build_path = project_path + '/gdx'
		project_build_path  = project_path + '/' + args.project_name

		os.environ['ANDROID_NDK'] = args.android_ndk

		if not os.path.exists(root_path + '/src/java'):
			args.gen_mode.append('android-src')

		if not os.path.exists(project_path):
			os.mkdir(project_path)

		if cleanup_and_prepare(gdx_build_path):
			call(['cmake', '-DCMAKE_BUILD_TYPE=Release', 
				'-DCMAKE_TOOLCHAIN_FILE=' + gdx_source_dir + '/cmake/android.toolchain.cmake'
		 , gdx_source_dir ])
		
		call(['make', '-j' + str(multiprocessing.cpu_count())])

		if cleanup_and_prepare(project_build_path):
			call(['cmake', '-DGDX_SOURCE=' + gdx_source_dir, 
				'-DCMAKE_TOOLCHAIN_FILE=' + gdx_source_dir + '/cmake/android.toolchain.cmake',
			    '-DGDX_ROOT=' + gdx_build_path, source_path])
			
		call(['make', '-j' + str(multiprocessing.cpu_count())])
		
		del os.environ["ANDROID_NDK"]

	if 'android-src' in args.gen_mode:
		os.chdir(root_path)
		java_src_path = root_path + '/src/java'
		activity = args.project_name[0].upper() + args.project_name[1:] + 'Activity'

		if cleanup_and_prepare(java_src_path):
			call(args.android_sdk + '/tools/android create project --target android-10 ' + 
				'--path ' + java_src_path + ' --activity ' + activity + ' --package ' + args.package_name, shell=True)

			os.chdir(java_src_path)
			os.mkdir('libs/armeabi-v7a')
			os.mkdir('assets')

			call(['ln', '-s', root_path + '/android/'+ args.project_name +'/lib/lib' + args.project_name + '.so', 'libs/armeabi-v7a' ])
			call(['ln', '-s', root_path + '/data', java_src_path + '/assets/data' ])

			write_template(gdx_source_dir + '/template/MainActivity.java', 
				root_path + '/src/java/src/' + args.package_name.replace('.','/'),
				activity + '.java', PackageName = args.package_name,
				ProjectName = args.project_name )

	if 'ios' in args.gen_mode:
		project_path = root_path + '/ios'
		gdx_build_path = project_path + '/gdx'		
		project_build_path  = project_path + '/' + args.project_name

		if not os.path.exists(project_path):
			os.mkdir(project_path)

		if not os.path.exists(source_path + '/Info.plist'):
			write_template(gdx_source_dir + '/template/Info.plist', source_path, 'Info.plist', 
				PackageName = args.package_name)
		
		if not os.path.exists(source_path + '/bind.mm'):
			call(['cp', gdx_source_dir + '/template/bind.mm', source_path])
		
		if cleanup_and_prepare(gdx_build_path):
			call(['cmake', '-DCMAKE_BUILD_TYPE=Release', '-GXcode','-DCOMPANY_NAME=' + args.package_name,
			'-DSDKVER=' + args.ios_sdk_ver, gdx_source_dir ])
		
		call(['xcodebuild', '-sdk', 'iphoneos'+ args.ios_sdk_ver, '-configuration', 'Release'])

		if cleanup_and_prepare(project_build_path):
			call(['cmake', '-DGDX_SOURCE=' + gdx_source_dir, '-DGDX_ROOT=' + gdx_build_path, '-GXcode', 
			 '-DCOMPANY_NAME=' + args.package_name, '-DSDKVER=' + args.ios_sdk_ver, source_path])

		call(['xcodebuild', '-sdk', 'iphoneos'+ args.ios_sdk_ver, '-configuration', 'Release'])
		
	if not args.gen_mode:
		print 'No target specified (--gen-mode). Exiting.'

if __name__ == "__main__": 
	setup()