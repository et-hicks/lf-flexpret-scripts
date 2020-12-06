// Code generated by the Lingua Franca compiler from file:
// /lf-flexpret-scripts/lf/timer/timer.lf
#include "ctarget.h"
#define NUMBER_OF_FEDERATES 1
#include "core/reactor.c"
// =============== START reactor class Timer
typedef struct {
    int bank_index;
    #line 6 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    int s;
    #line 7 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    long long _time;
    #line 9 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    reaction_t ___reaction_0;
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    trigger_t ___t;
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    reaction_t* ___t_reactions[1];
} timer_self_t;
void timerreaction_function_0(void* instance_args) {
    timer_self_t* self = (timer_self_t*)instance_args;
    #line 10 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->s += 1;
    self->_time = get_elapsed_physical_time();
        
}
timer_self_t* new_Timer() {
    timer_self_t* self = (timer_self_t*)calloc(1, sizeof(timer_self_t));
    #line 9 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___reaction_0.function = timerreaction_function_0;
    #line 9 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___reaction_0.self = self;
    #line 9 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___reaction_0.deadline_violation_handler = NULL;
    #line 9 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___reaction_0.tardy_handler = NULL;
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___t.last = NULL;
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___t_reactions[0] = &self->___reaction_0;
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___t.reactions = &self->___t_reactions[0];
    #line 5 "file:/lf-flexpret-scripts/lf/timer/timer.lf"
    self->___t.number_of_reactions = 1;
    self->___t.is_timer = true;
    return self;
}
void delete_Timer(timer_self_t* self) {
    if (self->___reaction_0.output_produced != NULL) {
        free(self->___reaction_0.output_produced);
    }
    if (self->___reaction_0.triggers != NULL) {
        free(self->___reaction_0.triggers);
    }
    if (self->___reaction_0.triggered_sizes != NULL) {
        free(self->___reaction_0.triggered_sizes);
    }
    for(int i = 0; i < self->___reaction_0.num_outputs; i++) {
        free(self->___reaction_0.triggers[i]);
    }
    free(self);
}
// =============== END reactor class Timer

void __set_default_command_line_options() {
}
// Array of pointers to timer triggers to be scheduled in __initialize_timers().
trigger_t* __timer_triggers[1];
int __timer_triggers_size = 1;
// Array of pointers to reactions to be scheduled in __trigger_startup_reactions().
reaction_t** __startup_reactions = NULL;
int __startup_reactions_size = 0;
// Empty array of pointers to shutdown triggers.
trigger_t** __shutdown_triggers = NULL;
int __shutdown_triggers_size = 0;
trigger_t* __action_for_port(int port_id) {
    return NULL;
}
void __initialize_trigger_objects() {
    // ************* Instance Timer of class Timer
    timer_self_t* timer_self = new_Timer();
    //***** Start initializing Timer
    static int timer_initial_s = 0;
    timer_self->s = timer_initial_s;
    timer_self->___t.offset = MSEC(100);
    timer_self->___t.period = 0;
    __timer_triggers[0] = &timer_self->___t;
    //***** End initializing Timer
    // Populate arrays of trigger pointers.
    timer_self->bank_index = 0;
    // Total number of outputs produced by the reaction.
    timer_self->___reaction_0.num_outputs = 0;
    // Allocate arrays for triggering downstream reactions.
    if (timer_self->___reaction_0.num_outputs > 0) {
        timer_self->___reaction_0.output_produced = (bool**)malloc(sizeof(bool*) * timer_self->___reaction_0.num_outputs);
        timer_self->___reaction_0.triggers = (trigger_t***)malloc(sizeof(trigger_t**) * timer_self->___reaction_0.num_outputs);
        timer_self->___reaction_0.triggered_sizes = (int*)malloc(sizeof(int) * timer_self->___reaction_0.num_outputs);
    }
    // Initialize the output_produced array.
    // Reaction 0 of Timer does not depend on one maximal upstream reaction.
    timer_self->___reaction_0.last_enabling_reaction = NULL;
    // doDeferredInitialize
    // Connect inputs and outputs for reactor Timer.
    // END Connect inputs and outputs for reactor Timer.
    
    timer_self->___reaction_0.chain_id = 1;
    // index is the OR of level 0 and 
    // deadline 140737488355327 shifted left 16 bits.
    timer_self->___reaction_0.index = 0x7fffffffffff0000LL;
}
void __trigger_startup_reactions() {
    
}
void __initialize_timers() {
    for (int i = 0; i < __timer_triggers_size; i++) {
        if (__timer_triggers[i] != NULL) {
            _lf_initialize_timer(__timer_triggers[i]);
        }
    }
}
void logical_time_complete(instant_t time) {
}
instant_t next_event_time(instant_t time) {
    return time;
}
bool __wrapup() {
    __start_time_step();  // To free memory allocated for actions.
    for (int i = 0; i < __shutdown_triggers_size; i++) {
        __schedule(__shutdown_triggers[i], 0LL, NULL);
    }
    // Return true if there are shutdown actions.
    return (__shutdown_triggers_size > 0);
}
void __termination() {}