void controller_init(){

        mthread_finished = malloc(sizeof(jmp_buf));

        // Load the configuration
        cinfo = config_handler_load();

        // Indicate that there is any thread running
        cinfo->running = 0;

        // Initialize thread environment
        mthread_init_environment(&wfinished);//mthread_finished);

        // Initialize the threads
        init_threads();
        
        if (cinfo->is_preemptive){
                // Initialize the timer
                set_timer(cinfo->quantum);
        }
        
        setup_interface();

        create_ui_main(cinfo->thread_list->count);

        launch_interface();
}
