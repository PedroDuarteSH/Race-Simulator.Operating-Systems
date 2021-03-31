//Processo responsável pela gestão da box e dos carros da equipa. É ainda responsável pela reparação dos carros da equipa e por atestar o depósito de combustível. Existe um por equipa.
//Fazer a Gestão da Box (APENAS 1) e Atualiza-a (Livre, Ocupada, reservada)
//Fazer a Gestão dos Carros da equipa
//Responsavel por reparações e atestar depósitos
#include "team_manager.h"


team *this_team;
car *shm_indexes;
pthread_t *cars;

void team_manager_start(int i){
    attach_update_team_shm(i);
    team_manager_init();
    //gestaoBox()
    //gerirAbastecimentoDosCarros
}
void team_manager_init(){
    print(concat("INITIATING TEAM CARS ARRAY ", this_team->name));
    cars =(pthread_t *) malloc(sizeof(pthread_t) * this_team->number_team_cars);
    shm_indexes = malloc(sizeof(int) * 1);
    //Colocar endereços de shared memory necessarios aos carros
    print(concat("STARTING TEAM CARS ", this_team->name));
    car ** team_cars;
    for(int i = 0;i < this_team->number_team_cars;i++){
        team_cars = shmat(this_team->cars_shmid, NULL, 0);
        shm_indexes = team_cars[i];
        pthread_create(&cars[i],NULL,car_init,&shm_indexes); //mudar o cars
    }
    print(concat("READY: CARS OF TEAM ", this_team->name));

    for(int i = 0;i < this_team->number_team_cars;i++){
        pthread_join(cars[i],NULL); //mudar o cars
    }
    print(concat("Team joined ", this_team->name));
    exit(0);
}


void attach_update_team_shm(int i){
    shm_struct = shmat(shm_id, NULL, 0);
    race_struct = shmat(shm_struct->race_shmid, NULL, 0);
    team **teams = shmat(race_struct->teams_shmid, NULL, 0);
    this_team = teams[i];
    shmdt(teams);
}

void *car_init(void * shm_ids){
    sleep(2);
    print("CAR RACING...");
    sleep(1);
    pthread_exit(NULL);
}