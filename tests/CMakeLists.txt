include_directories(${hw_INCDIR})

## Producer Consumer with Condition Variables
add_executable(test_producer_consumer_cond test_producer_consumer.cpp)
target_link_libraries(test_producer_consumer_cond cond_var gtest )
add_test(TestCondProducerConsumer ./test_producer_consumer_cond)

add_executable(test_producer_consumer_cond2 test_producer_consumer2.cpp)
target_link_libraries(test_producer_consumer_cond2 cond_var gtest )
add_test(TestCondProducerConsumer2 ./test_producer_consumer_cond2)

add_executable(test_pc_cond_while test_pc_while.cpp)
target_link_libraries(test_pc_cond_while cond_var gtest)
add_test(TestCondProducerConsumerWhile ./test_pc_cond_while)


## Producer Consumer with Semaphore
add_executable(test_producer_consumer_sem test_producer_consumer.cpp)
target_link_libraries(test_producer_consumer_sem semaphore gtest )
add_test(TestSemProducerConsumer ./test_producer_consumer_sem)

add_executable(test_producer_consumer_sem2 test_producer_consumer2.cpp)
target_link_libraries(test_producer_consumer_sem2 semaphore gtest )
add_test(TestSemProducerConsumer2 ./test_producer_consumer_sem2)


## Dining Philosophers no Circular Wait
add_executable(test_philosopher_circ test_philosopher.cpp)
target_link_libraries(test_philosopher_circ circular gtest )
add_test(TestCircPhilosopher ./test_philosopher_circ)


## Dining Philosophers no Hold and Wait
add_executable(test_philosopher_hold test_philosopher.cpp)
target_link_libraries(test_philosopher_hold hold_and_wait gtest )
add_test(TestHoldPhilosopher ./test_philosopher_hold)



