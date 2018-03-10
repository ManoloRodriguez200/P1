/*
 * Function to aproximate the PI value:
 * PI =  4 * arctan(1)  
 * = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 ... + (((-1)^n)/(2n + 1)))
 */
void calc_function(int thread_id){
        unsigned long long j = 0;
        long double pi = 0;
        long double divd = 1;
        long double sig = 1;

        struct mthread * thread = cinfo->thread_list->threads[cinfo->thread_list->thread_indexs[thread_id]];
        
        unsigned long long w = 0;
        int k = 0;

        thread->worku = 0; 
        j = 0;
        while (w < thread->workc){
                for (k = 0; k < WORKING_UNIT; k++){
                        pi += sig * ((long double)1/divd); 
                        thread->cvalue = pi * (long double)4;
                        divd += 2;
                        sig *= -1;
                        thread->worku++;
                        j++;
                        
                        /*
                         * Yield the processor if not preemtive scheduling and
                         * the allowed portion of the work is done.
                         * Note: We could code this in different way to prevent
                         * checking this condition every time but, coded this
                         * way is simple to undertand and, any way, the idea is
                         * to increase the processing load. 
                         */
                        if (!cinfo->is_preemptive && j > thread->ticketc * cinfo->quantum){
                                j = 0;
                                thread_value_changed(thread->id, thread->cvalue, WORKING_UNIT * thread->workc, thread->worku);
                                yield();
                        }
                }

                w++;
        }
}
