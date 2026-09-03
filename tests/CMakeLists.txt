include_directories(${hw_INCDIR})
include_directories(${src_INCDIR})

add_executable(proc_run_test proc_run_test.cpp)
target_link_libraries(proc_run_test homework)
add_test(ProcRunTests ./proc_run_test)
set_tests_properties(ProcRunTests PROPERTIES TIMEOUT 20)

add_executable(proc_order_test proc_order_test.cpp)
target_link_libraries(proc_order_test homework)
add_test(ProcOrderTests ./proc_order_test)
set_tests_properties(ProcOrderTests PROPERTIES TIMEOUT 20)

add_executable(proc_exit_test proc_exit_test.cpp)
target_link_libraries(proc_exit_test homework)
add_test(ProcExitTests ./proc_exit_test)
set_tests_properties(ProcExitTests PROPERTIES TIMEOUT 20)

add_executable(pri_run_test pri_run_test.cpp)
target_link_libraries(pri_run_test homework)
add_test(PriRunTests ./pri_run_test)
set_tests_properties(PriRunTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_run_test pri_rr_run_test.cpp)
target_link_libraries(pri_rr_run_test homework)
add_test(PriRRRunTests ./pri_rr_run_test)
set_tests_properties(PriRRRunTests PROPERTIES TIMEOUT 20)


add_executable(pri_order_test pri_order_test.cpp)
target_link_libraries(pri_order_test homework)
add_test(PriOrderTests ./pri_order_test)
set_tests_properties(PriOrderTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_order_test pri_rr_order_test.cpp)
target_link_libraries(pri_rr_order_test homework)
add_test(PriRROrderTests ./pri_rr_order_test)
set_tests_properties(PriRROrderTests PROPERTIES TIMEOUT 20)

add_executable(pri_high_test pri_high_test.cpp)
target_link_libraries(pri_high_test homework)
add_test(PriHighTests ./pri_high_test)
set_tests_properties(PriHighTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_high_test pri_rr_high_test.cpp)
target_link_libraries(pri_rr_high_test homework)
add_test(PriHighRRTests ./pri_rr_high_test)
set_tests_properties(PriHighRRTests PROPERTIES TIMEOUT 20)

add_executable(pri_timer pri_timer.cpp)
target_link_libraries(pri_timer homework)

add_executable(pri_fifo_test pri_fifo_test.cpp)
target_link_libraries(pri_fifo_test homework)
add_test(PriFIFOTests ./pri_fifo_test)
set_tests_properties(PriFIFOTests PROPERTIES TIMEOUT 20)

add_executable(pri_order_idx_test pri_order_idx_test.cpp)
target_link_libraries(pri_order_idx_test homework)
add_test(PriOrderIDXTests ./pri_order_idx_test)
set_tests_properties(PriOrderIDXTests PROPERTIES TIMEOUT 20)

add_executable(pri_order_simple_test pri_order_simple_test.cpp)
target_link_libraries(pri_order_simple_test homework)
add_test(PriOrderSimpleTests ./pri_order_simple_test)
set_tests_properties(PriOrderSimpleTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_fifo_test pri_rr_fifo_test.cpp)
target_link_libraries(pri_rr_fifo_test homework)
add_test(PriRRFIFOTests ./pri_rr_fifo_test)
set_tests_properties(PriRRFIFOTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_order_idx_test pri_rr_order_idx_test.cpp)
target_link_libraries(pri_rr_order_idx_test homework)
add_test(PriRROrderIDXTests ./pri_rr_order_idx_test)
set_tests_properties(PriRROrderIDXTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_order_simple_test pri_rr_order_simple_test.cpp)
target_link_libraries(pri_rr_order_simple_test homework)
add_test(PriRROrderSimpleTests ./pri_rr_order_simple_test)
set_tests_properties(PriRROrderSimpleTests PROPERTIES TIMEOUT 20)

add_executable(pri_rr_onestep_test pri_rr_onestep_test.cpp)
target_link_libraries(pri_rr_onestep_test homework)
add_test(PriRROneStepTests ./pri_rr_onestep_test)
set_tests_properties(PriRROneStepTests PROPERTIES TIMEOUT 20)


