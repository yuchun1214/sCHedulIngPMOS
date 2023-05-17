set(GIT_HOOKS_INSTALL ${PROJECT_SOURCE_DIR}/.git/hooks/installed)

set(scripts 
    commit-msg.sh
    pre-commit.sh
)

if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/.git)
    if(NOT WIN32 AND NOT EXISTS ${GIT_HOOKS_INSTALL})
        message(STATUS "Installing git hooks")
        foreach(script ${scripts})
            get_filename_component(basename ${script} NAME_WE)
            message(STATUS "Installing ${basename} hook")
            configure_file(${script} ${PROJECT_SOURCE_DIR}/.git/hooks/${basename} COPYONLY)
            execute_process(
                COMMAND chmod +x ${PROJECT_SOURCE_DIR}/.git/hooks/${basename}
            )
        endforeach()
        message(STATUS "Git hooks installed")
        execute_process(COMMAND touch ${GIT_HOOKS_INSTALL})  
    elseif()
        message(WARNING "In windows system, skipping hooks installation")
    endif()
elseif()
    message(WARNING "Not a git repository, skipping hooks installation")
endif()