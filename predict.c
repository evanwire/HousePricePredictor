#include<stdio.h>
#include<stdlib.h>

double** transpose(double**, int, int);
void freeMatrix(double**, int);
double** mult(double**, double**, int, int, int, int);
double** inverse(double**, int, int);
double* multMA(double**, double*, int, int);



int main(int argc, char ** argv){
  char * f1= argv[1];
  FILE * train = fopen(f1, "r");

  char * f2 = argv[2];
  FILE * test = fopen(f2, "r");
  
  if(f1 == NULL){
    printf("File %s does not exist.", f1);
    return 0;
  }

  if(f2 == NULL){
    printf("File %s does not exist.", f2);
    return 0;
  }

  int attributes;
  fscanf(train, "%d", &attributes);
  
  int numTraining;
  fscanf(train, "%d", &numTraining);

  double** trainingEX;
  trainingEX = malloc(numTraining * sizeof(double*));
  for(int i = 0; i < numTraining; i++){
    trainingEX[i] = malloc((attributes + 1) * sizeof(double));
  }

  
  double* housePrices;
  housePrices = malloc(numTraining * sizeof(double));
  

  for(int i = 0; i < numTraining; i++){
    for(int j = 0; j < attributes + 1; j++){
      if(j == attributes){
	double temp;
	fscanf(train, "%lf", &temp);
	housePrices[i] = temp;
      }else{
	double temp;
	fscanf(train, "%lf", &temp);
	trainingEX[i][j+1] = temp;
      }
      char c;
      fscanf(train, "%c", &c);
    }
  }
  for(int i = 0; i < numTraining; i++){
    trainingEX[i][0] = 1;
  }


  
  int numTesting;
  fscanf(test, "%d", &numTesting);

  double** testingEX;
  testingEX = malloc(numTesting * sizeof(double*));
  for(int i = 0; i < numTesting; i++){
    testingEX[i] = malloc((attributes+1) * sizeof(double));
  }

  for(int i = 0; i < numTesting; i++){
    for(int j = 0; j < attributes; j++){
      double temp;
      fscanf(test, "%lf", &temp);
      testingEX[i][j+1] = temp;
      char c;
      fscanf(test, "%c", &c);
    }
  }
  for(int i = 0; i < numTesting; i++){
    testingEX[i][0] = 1;
  }



  //attributes+1 x numTraining
  double** transTraining = transpose(trainingEX, numTraining, attributes+1);

  
  //attributes+1 x attributes+1
  double** transTimesTrain = mult(transTraining, trainingEX, attributes+1, numTraining, numTraining, attributes+1);



  //attributes+1 x attributes+1
  double** inverseTransTimesTrain = inverse(transTimesTrain, attributes+1, attributes+1);


  

  //attributes+1 * numTraining
  double** inverseTimesTrans = mult(inverseTransTimesTrain, transTraining, attributes+1, attributes+1, attributes+1, numTraining);



  
  
  //numTraining x 1
  double* weights = multMA(inverseTimesTrans, housePrices, attributes+1, numTraining);

  
  double* predictedPrices = multMA(testingEX, weights, numTesting, attributes+1);
  
  int* integerPrices = malloc(numTesting * sizeof(int));
  for(int i = 0; i < numTesting; i++){
    integerPrices[i] = (int)(predictedPrices[i] + 0.5);
  }

  for(int i = 0; i < numTesting; i++){
    printf("%d\n", integerPrices[i]);
  }

  

  free(integerPrices);

  free(predictedPrices);

  free(weights);

  freeMatrix(inverseTransTimesTrain, attributes);

  freeMatrix(transTimesTrain, attributes);

  freeMatrix(transTraining, attributes);

  freeMatrix(trainingEX, numTraining);

  free(housePrices);

  freeMatrix(testingEX, numTesting);


  return 0;
}


  
double** transpose(double** matrix, int h, int w){
  double** trans;
  trans = malloc(w * sizeof(double*));
  for(int i = 0; i < w; i++){
    trans[i] = malloc(h * sizeof(double));
  }
  
  
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      trans[j][i] = matrix[i][j];
    }
  }
  
  return trans;
}
  
void freeMatrix(double** matrix, int h){
  for(int i = 0; i < h; i++){
    free(matrix[i]);
  }
  free(matrix);
}


//Pretty much coppied my own code for multiplying matrices from pa1, in case this flags as plagiarism
double** mult(double** m1, double** m2, int m1Rows, int m1Cols, int m2Rows, int m2Cols){
  if(m1Cols != m2Rows){
    printf("\n\n matrices are not compatable, cannot multiply \n\n");

    return m1;
  }


  double** result;
  result = malloc(m1Rows * sizeof(double*));
  for(int i = 0; i < m1Rows; i++){
    result[i] = malloc(m2Cols * sizeof(double));
  }

  for(int i = 0; i < m1Rows; i++){
    for(int x = 0; x < m2Cols; x++){
      double temp = 0;
      for(int j = 0; j < m2Rows; j++){
	temp += m1[i][j] * m2[j][x];
      }
      result[i][x] = temp;
    }
  }

  return result;

}


double** inverse(double** matrix, int rows, int cols){

  if(cols != rows){
    printf(" \n\n matrix is not square, cannot invert \n\n");
    return matrix;
  }
  
  double ditto[rows][cols];


  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      ditto[i][j] = matrix[i][j];
    }
  }

  double** aug;
  aug = malloc(rows * sizeof(double));
  for(int i = 0; i < rows; i++){
    aug[i] = malloc(cols * sizeof(double));
  }
  
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      if(i == j){
        aug[i][j] = 1;
      }else{
        aug[i][j] = 0;
      }
    }
  }
  

  

  
  for(int i = 0; i < rows; i++){
    if(ditto[i][i] != 1){
      double constant = ditto[i][i];
      for(int x = 0; x < rows; x++){
	
	ditto[i][x] = ditto[i][x] / constant;

	aug[i][x] = aug[i][x] / constant;

      }
    }
    
    for(int x = i + 1; x < rows; x++){
      double constant = ditto[x][i];
      for(int y = 0; y < rows; y++){
	ditto[x][y] = ditto[x][y] - (ditto[i][y] * constant);
	aug[x][y] = aug[x][y] - (aug[i][y] * constant);

      }
    }


  }
  
  for(int i = rows -1; i > -1; i--){
    for(int x = i - 1; x > -1; x--){
      double constant = ditto[x][i];
      for(int y = 0; y < rows; y++){
	ditto[x][y] = ditto[x][y] - (ditto[i][y] * constant);
	aug[x][y] = aug[x][y] - (aug[i][y] * constant);
		
      }
    }
  }



  return aug;

	
  
}

double* multMA(double** matrix, double* arr, int r, int c){
  double* result;
  result = malloc(r * sizeof(double));

  for(int i = 0; i < r; i++){
    double temp = 0;
    for(int j = 0; j < c; j++){
      temp += matrix[i][j] * arr[j];
    }
    result[i] = temp;
  }
  
  return result;

}
