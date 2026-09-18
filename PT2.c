// Μπουζούκας Κωνσταντίνος - Λευτέρης   5302
// Νικολακόπουλος Αριστείδης            5308
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define D 2
#define K 4
#define H1 20
#define H2 10
#define ACTIVATION_RELU 1
#define ACTIVATION_TANH 0
#define MIN_EPOCHS 800
#define MAX_ERROR 0.001
#define LEARNING_RATE 0.001
#define N 4000
#define B 20

//Weights and Biases for each level
//Inp -> H1
double weights_inp_to_h1[D][H1];
double der_errors_w_inp_to_h1[D][H1];

double bias_h1[H1];
double der_errors_b_h1[H1];

double h1_total_inputs[H1];
double h1_outputs[H1];

//H1 -> H2
double weights_h1_to_h2[H1][H2];
double der_errors_w_h1_to_h2[H1][H2];

double bias_h2[H2];
double der_erros_b_h2[H2];

double h2_total_inputs[H2];
double h2_outputs[H2];

//H2 -> Out
double weights_h2_to_out[H2][K];
double der_errors_w_h2_to_out[H2][K];

double bias_out[K];
double der_errors_b_out[K];

double outs[K];
double *outputs;

//struct to hold info on each pair (x1,x2) with their ideal output vectors
typedef struct pairs_with_vec{
    double vec[4];
    double x[2];
}examples;

//making the values for each pair according to the Data
examples make_pair(char str_to_make_double[]){
            examples ll;
            int temp = 0;

            char temp_str_x1[11];
            char *end;
            char temp_str_x2[11];
            char *end2;
            char temp_str_class[20];
           

           while(str_to_make_double[temp]!=','){
                temp_str_x1[temp] = str_to_make_double[temp];
                temp++;
            }
            ll.x[0] = strtod(temp_str_x1,&end);

            
            temp++;
            int temp2 = 0;
            while(str_to_make_double[temp]!=','){
                temp_str_x2[temp2] = str_to_make_double[temp];
                temp++;
                temp2++;
            }
            
            ll.x[1] = strtod(temp_str_x2,&end2);
            for(int i = 0;i<4;i++){
                ll.vec[i] = 0;
            }
            
            temp_str_class[0] = str_to_make_double[temp+2];
            temp_str_class[1] = str_to_make_double[temp+3];

            int vec_index = (int)temp_str_class[1] -49;
            ll.vec[vec_index] = 1;

           
        return ll;
     
}

double make_random_in_range(){
    
    int negInd = (rand() % 2);
    double ret = (float)rand()/RAND_MAX;
    if(negInd == 1){
        ret *=-1;
    }
    return ret;
}

double relu(double u){
    if(u>0){
        return u;
    }else{
        return 0;
    }
}

double derivative_relu(double u){
    if(u>0){
        return 1;
    }else{
        return 0;
    }
}

double tanhu(double u) {
    return tanh(u);
}

double derivative_tanhu(double u){
    return 1 - tanhu(u)*tanhu(u);
}

double func_activation(double u,int activation_code){
    if(activation_code == ACTIVATION_RELU){
        return relu(u);
    }
    else{
        return tanhu(u);
    }
}

double derivative_activation(double u,int activation_code){
    if(activation_code == ACTIVATION_RELU){
        return derivative_relu(u);
    }else{
        return derivative_tanhu(u);
    }
}

double *output_function(double y[],int k){
    double ey[k];
    for(int i =0;i<k;i++){
        ey[i] = exp(y[i]);
    }
    double sum = 0;
    for(int i =0;i<k;i++){
        sum += ey[i];
    }
    double *ret;
    ret = (double*)malloc(k*sizeof(double));
    for(int i =0;i<k;i++){
        ret[i] = ey[i]/sum;
    }
    
    return ret;
}

double* forward_pass(double *x,int d,double *y,int k){
    
    //From inputs to H1
    for(int i =0;i<H1;i++){
        double temp =0;
        for(int  j =0;j<d;j++){
            temp += x[j] * weights_inp_to_h1[j][i];
        }
        temp+=bias_h1[i];
        h1_total_inputs[i] = temp;
        h1_outputs[i] = func_activation(temp,ACTIVATION_TANH);
    }

    //From H1 to H2
    for(int i =0;i<H2;i++){
        double temp =0;
        for(int  j =0;j<H1;j++){
            temp += h1_outputs[j] * weights_h1_to_h2[j][i];
        }
        temp+=bias_h2[i];
        h2_total_inputs[i] = temp;
        h2_outputs[i] = func_activation(temp,ACTIVATION_TANH);
    }

    for(int i =0;i<k;i++){
        double temp =0;
        for(int  j =0;j<H2;j++){
            temp += h2_outputs[j] * weights_h2_to_out[j][i];
        }
        temp+=bias_out[i];
        outs[i] = temp;

    }
    y = output_function(outs,k);
   
    return y;
}
   
void backprop(double *x, int d, double *t, int k){
    //H2 -> K
    double delta_out[k];
    for(int i = 0;i<k;i++){
        delta_out[i] = outputs[i] - t[i];
        der_errors_b_out[i] = delta_out[i];
        for(int j = 0;j<H2;j++){
            der_errors_w_h2_to_out[j][i] = h2_outputs[j] * delta_out[i];
        }
    }

    //H1 -> H2
    double delta_H2[H2];
    
    for(int i = 0;i<H2;i++){
        double temp = 0;
        for(int j= 0;j<k;j++){
            temp += weights_h2_to_out[i][j]*delta_out[j];
        }

        delta_H2[i] = derivative_activation(h2_total_inputs[i],ACTIVATION_TANH)*temp;
        der_erros_b_h2[i] = delta_H2[i];

        for(int j= 0;j<H1;j++){
           der_errors_w_h1_to_h2[j][i] = h1_outputs[j]*delta_H2[i];
        }
    }
    
    //Inp -> H1
    double delta_H1[H1];
    for(int i = 0;i<H1;i++){
        double temp = 0;
        for(int j = 0;j<H2;j++){
            temp += weights_h1_to_h2[i][j]*delta_H2[j];
        }

        delta_H1[i] = derivative_activation(h1_total_inputs[i],ACTIVATION_TANH)*temp;
        der_errors_b_h1[i] = delta_H1[i];
       
        for(int j = 0;j<d;j++){
            der_errors_w_inp_to_h1[j][i] = x[j] * delta_H1[i];
        }

    }




}


int main(){
    srand(time(NULL));
    //opening files to import the examples
    FILE *training_data_f;
    training_data_f = fopen("trainingData.csv", "r+");
    FILE *check_data_f;    
    check_data_f = fopen("checkData.csv", "r+");
   
    //creating the examples in two arrays (training_data,check_data) of 4000 examples each
    char myStr[27];

    examples check_data[4000];

    fgets(myStr,27,check_data_f);
    for(int i = 0;i<4000;i++){
        fgets(myStr,27,check_data_f);
        check_data[i] = make_pair(myStr);
    }

    examples training_data[N];   
    fgets(myStr,27,training_data_f);
    for(int i = 0;i<N;i++){
        fgets(myStr,27,training_data_f);
        training_data[i] = make_pair(myStr);
    }
    
    

    //***** initialize weights and biases *****

    //weights D to H1 and biases of H1
    for(int i =0; i< H1;i++){
        bias_h1[i] = make_random_in_range();
        for(int j = 0;j<D;j++){
            weights_inp_to_h1[j][i] = make_random_in_range();
        }
    }

    //weights H1 to H2 and biases of H2
    for(int i =0; i< H2;i++){
        bias_h2[i] = make_random_in_range();
        for(int j = 0;j<H1;j++){
            weights_h1_to_h2[j][i] = make_random_in_range();
        }
    }

    //weights H2 to out and biases of out
    for(int i =0; i< K;i++){
        bias_out[i] = make_random_in_range();
        for(int j = 0;j<H2;j++){
            weights_h2_to_out[j][i] = make_random_in_range();
        }
    }
    outputs = (double*)malloc(sizeof(double)*4);

    

    int t = 0;
    double total_error = 0;
    double previous_error = 0;
    int a = 800;
    do{
        if(t > 8000){
            printf("\nTotal Error = %lf\n",total_error);
            break;
        }
        total_error = 0;        
        
        int index = 0;
        for(int i = 0;i<N/B;i++){
            double temp_der_w_inp_to_h1[D][H1];
            memset(temp_der_w_inp_to_h1, 0, sizeof(temp_der_w_inp_to_h1));

            double temp_der_b_h1[H1];
            memset(temp_der_b_h1, 0, sizeof(temp_der_b_h1));

            double temp_der_w_h1_to_h2[H1][H2];
            memset(temp_der_w_h1_to_h2, 0, sizeof(temp_der_w_h1_to_h2));

            double temp_der_b_h2[H2];
            memset(temp_der_b_h2, 0, sizeof(temp_der_b_h2));
           
            double temp_der_w_h2_to_out[H2][K];
            memset(temp_der_w_h2_to_out, 0, sizeof(temp_der_w_h2_to_out));

            double temp_der_b_out[K];
            memset(temp_der_b_out, 0, sizeof(temp_der_b_out));

            //1 Batch
           
            for(int j = 0;j<B;j++){
                examples ex = training_data[index];
                
                outputs = forward_pass(ex.x,D,outputs,K);
                
                backprop(ex.x,D,ex.vec,K);
               
                for(int i = 0;i<H1;i++){
                    temp_der_b_h1[i] += der_errors_b_h1[i];
                    for(int j = 0;j<D;j++){
                        temp_der_w_inp_to_h1[j][i] += der_errors_w_inp_to_h1[j][i];
                    }
                }
                for(int i = 0;i<H2;i++){
                    temp_der_b_h2[i] += der_erros_b_h2[i];
                    for(int j = 0;j<H1;j++){
                        temp_der_w_h1_to_h2[j][i] += der_errors_w_h1_to_h2[j][i];
                    }
                }
                for(int i = 0;i<K;i++){
                    temp_der_b_out[i] += der_errors_b_out[i];
                    for(int j = 0;j<H2;j++){
                        temp_der_w_h2_to_out[j][i] += der_errors_w_h2_to_out[j][i];
                    }
                }

                double temp = 0;
                for(int i =0;i<K;i++){
                    temp += (ex.vec[i] - outputs[i]) * (ex.vec[i] - outputs[i]);
                }
                temp = temp/2;
                total_error += temp;
                
                index++;
            }

            //Weights and Bias Update
            for(int i = 0;i<H1;i++){
                bias_h1[i] -= LEARNING_RATE*temp_der_b_h1[i];
                for(int  j = 0; j<D;j++){
                    weights_inp_to_h1[j][i] -= LEARNING_RATE*temp_der_w_inp_to_h1[j][i];
                }
            }
            for(int i = 0;i<H2;i++){
                bias_h2[i] -= LEARNING_RATE*temp_der_b_h2[i];
                for(int  j = 0; j<H1;j++){
                    weights_h1_to_h2[j][i] -= LEARNING_RATE*temp_der_w_h1_to_h2[j][i];
                }
            }
            for(int i = 0;i<K;i++){
                bias_out[i] -= LEARNING_RATE*temp_der_b_out[i];
                for(int  j = 0; j<H2;j++){
                    weights_h2_to_out[j][i] -= LEARNING_RATE*temp_der_w_h2_to_out[j][i];
                }
            }
            

        }

        
        total_error = total_error/N;
        
            printf("\n************ EPOCH = %d ***********\nTotal Error = %lf\n",t,total_error);
        
        if(fabs(total_error - previous_error) < MAX_ERROR && t > MIN_EPOCHS){
            break;
        }
        previous_error = total_error;
        t++;
    }while(1);//(!(total_error < MAX_ERROR && t > MIN_EPOCHS));   


    double counter = 0;
    for(int i = 0;i<N;i++){
        examples ex = check_data[i];
        outputs = forward_pass(ex.x,D,outputs,K);
        
        int temp = 0;
        for(int j = 1;j<4;j++){
            if(outputs[temp] < outputs[j]){
                temp = j;
            }
        }
        
        int correct;
        for(int j =0;j<4;j++){
            if(ex.vec[j] == 1){
                correct = j;
            }
        }
      
        if(temp == correct){
            
            counter++;
        }
        
    }
    counter = (counter/N)*100;
    printf("\nCorrect Choice Rate = %lf\n",counter);

    
    
    



    //closing files
    free(outputs);
    fclose(training_data_f);
    fclose(check_data_f);
    printf("Exited With %d;\n",B);
    return 0;
}