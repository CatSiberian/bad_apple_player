file(GET_RUNTIME_DEPENDENCIES
    EXECUTABLES ${EXECUTABLE}
    RESOLVED_DEPENDENCIES_VAR RESOLVED_DEPS
    UNRESOLVED_DEPENDENCIES_VAR UNRESOLVED_DEPS
    DIRECTORIES ${SEARCH_DIRS}
)

# Копируем каждую найденную библиотеку в папку с EXE
foreach(file ${RESOLVED_DEPS})
    # Нам нужны только файлы из MinGW (игнорируем системные из System32)
    if(file MATCHES "msys64")
        file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
endforeach()

# Вывод для отладки, если что-то не найдется
foreach(file ${UNRESOLVED_DEPS})
    message(STATUS "Unresolved: ${file}")
endforeach()
