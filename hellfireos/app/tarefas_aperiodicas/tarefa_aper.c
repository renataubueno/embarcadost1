//foi usado como base o sched_test2.c
#include <hellfire.h>

//tarefa Polling Server - a geração dessa tarefa segue o mesmo formato da de tempo real
void task_polling_server(void){
	int32_t jobs, id;

	printf("HI");
	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("\n%s (%d)[%d][%d]", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

//tarefa de tempo real
void task_tempo_real(void){
	int32_t jobs, id;

	id = hf_selfid();
	for(;;){
		jobs = hf_jobs(id);
		printf("\n%s (%d)[%d][%d]", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

//tarefa best-effort (disparo de uma tarefa aperiódica entre 50ms e 500ms)
void task_best_effort(void){
	int32_t jobs, id;

	id = hf_selfid();
	for(;;){
		delay_ms(50 + (random() % 450));
		int32_t i = hf_spawn(task_polling_server, 0, 20, 0, "tarefa aperiódica", 2048);
		printf("\n%d", i);
		//trigga o spawn da tarefa aperiódica depois de um random entre 50 e 500
		//tirando isso, o restante do funcionamento da tarefa é igual ao de tempo real
		jobs = hf_jobs(id);
		printf("\n%s (%d)[%d][%d]", hf_selfname(), id, hf_jobs(id), hf_dlm(id));
		while (jobs == hf_jobs(id));
	}
}

void app_main(void){
	hf_spawn(task_tempo_real, 4, 1, 4, "tarefa de tempo real", 2048);
	hf_spawn(task_best_effort, 0, 0, 0, "tarefa de best effort", 2048); 
	//conforme a definição do hf_spawn(), If a task has defined realtime parameters, it is put on the RT queue, if not (period 0, capacity 0 and deadline 0), it is put on the BE queue.
}
