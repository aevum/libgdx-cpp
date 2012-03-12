#This macro has the task to figure out how the application is supposed to run
#on each backend.
macro(gdx_setup_runnable_target target_name sources) 

	if (APPLE) 
		add_executable(${target_name} MACOSX_BUNDLE ${sources})

    	SET(SDKVER "5.0")
    
    	execute_process(COMMAND xcode-select -print-path OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
		set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")

		SET(DEVROOT "${_output}/iPhoneOS.platform/Developer")
		SET(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
		SET(CMAKE_OSX_SYSROOT "${SDKROOT}")

		SET (CMAKE_OSX_ARCHITECTURES "$(ARCHS_UNIVERSAL_IPHONE_OS)")
   
    	set(CMAKE_CXX_FLAGS "-x objective-c++ -mno-thumb")
    	set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenGLES -framework AVFoundation")

        set_target_properties(${target_name} PROPERTIES
  			MACOSX_BUNDLE_GUI_IDENTIFIER "\${PRODUCT_NAME:identifier}"
 			RESOURCE "${RESOURCES}"
  			XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
  			XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
 			XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER YES  		
            XCODE_ATTRIBUTE_INFOPLIST_PREPROCESS YES
  			XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 4.3 # minimum deployment target
  			XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2" # target both iPhone and iPad
  			XCODE_ATTRIBUTE_SKIP_INSTALL NO # needed for archive to actually show up in organizer
  			XCODE_ATTRIBUTE_INSTALL_PATH "/Application" # Archiving doesn't work with an empty path
	    )
	    
		#if(resource_folder) 
		#	add_custom_command(
    	#		TARGET ${target_name}
    	#		POST_BUILD
    	#		COMMAND ${_output}/../OtherFrameworks/DevToolsCore.framework/Versions/A/Resources/pbxcp -exclude .DS_Store -exclude CVS -exclude .svn -resolve-src-symlinks ${RES_DIR} ${APP_NAME}
		#		)
		#endif()
		
	elseif (ANDROID_NDK)
		add_library(${target_name} SHARED ${sources})
	
	elseif(UNIX)
		add_executable(${target_name} ${sources})	
	endif()

endmacro()