#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <cuda_runtime.h>

#include "cublas_v2.h"
#include "generateRayleighScalarNoise.c"


int main() {
    int M,N;
    int kboucle;


    FILE *fichier1;
    fichier1=fopen("../results/results_cuda_gemm_fp64.dat","w");


    /* Debut grand boucle */
    for (kboucle=1 ; kboucle<31 ;kboucle++) {

        M=100*kboucle;
        N=M;

        printf(">>>>> Matrix size %dx%d  <<<<<<\n",M,N);

        int iboucle,jboucle,dim;
        int param=20;
        float *mat_real,*mat_imag;
        float charge;

        cublasStatus_t status ;

        // Chronometre

        struct timespec tpdeb,tpfin,tpcour;
        clockid_t clock_id=CLOCK_REALTIME;
        int status2;

        float dureeloc,dureetot;
        dureetot=0.0;

        // BLAS

        cublasOperation_t transa,transb;


        /* CUBLAS */

        float time1,time2;
        cudaEvent_t start1,start2, stop;

        cuDoubleComplex cualpha,cubeta;
        cuDoubleComplex *h_A,*h_B;
        cuDoubleComplex *h_C;
        cuDoubleComplex* d_A;
        cuDoubleComplex* d_B;
        cuDoubleComplex* d_C;

        transa=CUBLAS_OP_N;
        transb=CUBLAS_OP_N;


        cualpha.x=1.0;
        cualpha.y=0.0;
        cubeta.x=0.0;
        cubeta.y=0.0;

        dim=M;

        mat_real=(float*)calloc(M*N,sizeof(float));
        mat_imag=(float*)calloc(M*N,sizeof(float));

        h_A=(cuDoubleComplex*)calloc(M*N,sizeof(cuDoubleComplex));
        h_B=(cuDoubleComplex*)calloc(M*N,sizeof(cuDoubleComplex));
        h_C=(cuDoubleComplex*)calloc(M*N,sizeof(cuDoubleComplex));

        /* Initialize CUBLAS */

        cublasHandle_t handle;
        status=cublasCreate(&handle);

        cudaMalloc((void**)&d_A, M*N*sizeof(cuDoubleComplex));
        cudaMalloc((void**)&d_B, M*N*sizeof(cuDoubleComplex));
        cudaMalloc((void**)&d_C, M*N*sizeof(cuDoubleComplex));
        //status = cublasAlloc(M*N, sizeof(cuDoubleComplex), (void**)&d_A);
        //status = cublasAlloc(M*N, sizeof(cuDoubleComplex), (void**)&d_B);
        //status = cublasAlloc(M*N, sizeof(cuDoubleComplex), (void**)&d_C);
        //  if (status != CUBLAS_STATUS_SUCCESS) {
        //   fprintf (stderr, "!!!! device memory allocation error (B)\n");
        // return EXIT_FAILURE;
        //}

        printf("Generation de la matrice \n");

        for (iboucle=0 ; iboucle<M*N ; iboucle++) {
            generateRayleighScalarNoise(param,mat_real+iboucle,mat_imag+iboucle);
        }

        printf("Hermitien de la matrice\n");


        for(iboucle=0 ; iboucle<N*N ; iboucle++) {
            h_A[iboucle].x=mat_real[iboucle];
            h_A[iboucle].y=mat_imag[iboucle];
            h_B[iboucle].x=mat_imag[iboucle];
            h_B[iboucle].y=mat_real[iboucle];
        }

        /* %%%%% Calcul avec CULA  %%%%%%%%%*/

        printf("Benchmarking.....\n");

        // Remise a zero et deuxieme chorno

        struct timespec tpdeb2,tpfin2;
        float dureeloc2,dureetot2;

        dureeloc=0.0;
        dureetot=0.0;

        cudaEventCreate(&start1);
        cudaEventCreate(&stop);
        status2=clock_gettime(clock_id, &tpdeb);

        cudaEventCreate(&start1);
        cudaEventCreate(&stop);

        // Copie de la matrice dans le GPU

        status = cublasSetVector(M*N, sizeof(cuDoubleComplex), h_A, 1, d_A, 1);
        status2 = clock_gettime(clock_id, &tpdeb2);

        cudaThreadSynchronize();
        cudaEventRecord(start1, 0);

        cublasZgemm(handle,transa,transb,dim,dim,dim,&cualpha,d_A,dim,d_B,dim,&cubeta,d_C,dim);


        cudaThreadSynchronize();
        cudaEventRecord( stop, 0);

        status2=clock_gettime(clock_id, &tpfin2);

        // Copie matrice(vecteurs propres) + valeurs propres dans le host

        status = cublasGetVector(M*N, sizeof(cuDoubleComplex), d_C, 1, h_C, 1);

        if (status != CUBLAS_STATUS_SUCCESS) {
            fprintf (stderr, "!!!! device access error (read C)\n");
            return EXIT_FAILURE;
        }

        status2=clock_gettime(clock_id, &tpfin);
        dureeloc=(float)(tpfin.tv_sec-tpdeb.tv_sec)+(float)(tpfin.tv_nsec-tpdeb.tv_nsec)*1.e-9;
        dureetot=dureetot+dureeloc;

        cudaEventElapsedTime( &time1, start1, stop );
        cudaEventDestroy( start1 );
        cudaEventDestroy( stop );
        printf("Timeur CUDA = %f ms\n",time1);


        printf("Temps CUDA avec transfert = %f ms\n",dureeloc*1000);

        //fprintf(fichier2,"%20.15f\n",time1);

        dureeloc2=(float)(tpfin2.tv_sec-tpdeb2.tv_sec)+(float)(tpfin2.tv_nsec-tpdeb2.tv_nsec)*1.e-9;
        dureetot2=dureetot2+dureeloc2;

        printf("Temps CUDA sans transfert = %f ms\n",dureeloc2*1000);
        // fprintf(fichier3,"%20.15f\n",dureeloc2);

        charge=(float)M;
        charge=8*charge*charge*charge;
        charge=charge/dureeloc2;
        printf("compute power = %f GFLOP\n",charge/1e9);
        fprintf(fichier1,"%20.15f\n",charge/1e9);

        cudaFree(d_A);
        cudaFree(d_B);
        cudaFree(d_C);

        cublasDestroy ( handle ) ;



        free(mat_real);
        free(mat_imag);

        free(h_A);
        free(h_B);
        free(h_C);

        printf("Fin calcul de la matrice %dx%d\n",M,N);
    }

    fclose(fichier1);

    return 0;
}
