#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 10  //number of guests
#define EATING 0
#define HUNGRY 1
#define FUN 2


int food_list[3] = {5,5,5};
int donut =30;
int cake = 15;
int drink = 30;
int state[N];
int guests[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

sem_t mutex;
sem_t S[N];

void test(int guest_no)
{
    char food_drink[10];

    if (state[guest_no] == HUNGRY) {

        // state that eating

        printf("Please enter, what you want to eat?:\n");
        scanf("%s",food_drink);

        if((strcmp(food_drink,"donut")==0)){

            if (donut == 0)
                printf("Donuts are over.\n");

            else{
                state[guest_no] = EATING;
                food_list[0]=food_list[0]-1;
                donut--;

                printf("The number of Donuts left on the tray: %d\n",food_list[0]);
                printf("donut :%d\n",donut);

                if(food_list[0]==1){
                    printf("To the attention of the Waiter, tray is empty.\n");

                    if(donut >= 0){
                        if(donut<5)
                            food_list[0] += (donut-1);
                        else
                            food_list[0] += 4;
                    }
                }
                sleep(2);
                printf("Guest %d takes %s.\n", guest_no + 1, food_drink);
                printf("Guest %d is Eating.\n", guest_no + 1);
                sem_post(&S[guest_no]);
            }
        }

        if((strcmp(food_drink,"cake")==0)){
            if (cake == 0)
                printf("Cakes are over.\n");

            else{
                state[guest_no] = EATING;
                food_list[1]=food_list[1]-1;
                cake--;

                printf("The number of Cakes left on the tray: %d\n", food_list[1]);
                printf("cake :%d\n", cake);

                if(food_list[1]==1){
                    printf("To the attention of the Waiter, tray is empty.\n");

                    if(cake >= 0){
                        if(cake<5)
                            food_list[1] += (cake-1);
                        else
                            food_list[1] += 4;
                    }
                }

                sleep(2);
                printf("Guest %d takes %s.\n", guest_no + 1, food_drink);
                printf("Guest %d is Eating.\n", guest_no + 1);
                sem_post(&S[guest_no]);
            }
        }

        if((strcmp(food_drink,"drink")==0))
        {
            if (drink == 0)
                printf("Drinks are over.\n");

            else
            {
                state[guest_no] = EATING;
                food_list[2]=food_list[2]-1;
                drink--;

                printf("The number of Drinks left on the tray: %d\n",food_list[2]);
                printf("drink :%d\n",drink);

                if(food_list[2]==1)
                {
                    printf("To the attention of the Waiter, tray is empty.\n");
                    if(drink >= 0)
                    {
                        if(drink<5)
                            food_list[2] += (drink-1);
                        else
                            food_list[2] += 4;
                    }
                }
                sleep(2);
                printf("Guest %d takes %s.\n", guest_no + 1, food_drink);
                printf("Guest %d is Eating.\n", guest_no + 1);
                sem_post(&S[guest_no]);
            }
        }

    }
}


void take_eat(int guest_no)
{

    sem_wait(&mutex);

    // state that hungry
    state[guest_no] = HUNGRY;

    printf("Guest %d is Hungry\n", guest_no + 1);

    // eat if guests are not eating
    test(guest_no);

    sem_post(&mutex);

    // if unable to eat wait to be signalled
    sem_wait(&S[guest_no]);

    sleep(1);
}

int fill_food(int guest_no)
{

    sem_wait(&mutex);
    // state that fun
    state[guest_no] = FUN;

    return cake, donut, drink;

    sem_post(&mutex);
}

void* guest(void* num)
{

    while (1) {

        int* i = num;

        sleep(1);

        take_eat(*i);

        sleep(0);

        fill_food(*i);
    }
}

int main()
{

    int i;
    pthread_t thread_id[N];

    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++)

        printf("Guest %d is waiting\n", i + 1);


        //while(1)
        for (i = 0; i < 75; i++){
        //int j = 0;
        // create guests processes
        pthread_create(&thread_id[i], NULL, guest, &guests[i]);
        //j++;
    }

      while(donut != 0 && cake != 0 && drink != 0){

        pthread_join(thread_id[i], NULL);

      }
}
