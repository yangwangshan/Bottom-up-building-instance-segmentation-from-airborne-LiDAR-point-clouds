Project(building instance segmentation)
file (GLOB HEADERS "*.h" "*.hpp")
file (GLOB SOURCES "*.cpp")

set(ALL_SRCS ${HEADERS} ${SOURCES})

add_executable (${PROJECT_NAME}
	${ALL_SRCS})

target_include_directories(${PROJECT_NAME}
	PUBLIC ${EIGEN_INCLUDE_DIRS}
		${PCL_INCLUDE_DIRS}
		${OPENCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
	${PCL_LIBRARIES}
	${NEEDED_OPENCV_MODULE}
	)
if (LASLIB_FOUND)
	target_include_directories(${PROJECT_NAME} PUBLIC
		${LASLIB_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${LASLIB_LIBRARIES})
endif (LASLIB_FOUND)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "stocker_tools") 