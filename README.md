## Project Description

The price of a house (y) can depend on various things. These attributes include the number of bedrooms (x1), the size of the house (x2), the number of bathrooms (x3), and the year the house was built (x4). However, these attributes do not equally contribute to the price of the house, some of these features matter more than others. If we know how each attribute was weighted, or how much each attribute mattered when calculating the price of a house, we could make relatively accurate predictions on the prices of houses when we only have access to the attributes of the house. Linear Regression is an algorithm that helps find these aformentioned weights (w1, w2, w3, w4). Once the weights are found, the price of any house can be predicted with the following formula (assuming we know all of the house's attributes):

>y = w0 + w1.x1 + w2.x2 + w3.x3 + w4.x4<br>
*You might notice this looks awfully like the equation for a line, hence the linear from the name linear regression*

### To Run

In the project directory, run the following two commands:

>make<br>
>./predict \<train-data-file-name\>.txt \<test-data-file-name\>.txt

### Structure of the training data file

The first line should be an integer that provides the number of attributes in the training set. The second line should be an integer providing the number of training examples in the training dataset. The rest of the file should be the actual training examples, which each should be comma separated floating point values.

An example training data file is shown below:

4<br>
7<br>
3.000000,1.000000,1180.000000,1955.000000,221900.000000<br>
3.000000,2.250000,2570.000000,1951.000000,538000.000000<br>
2.000000,1.000000,770.000000,1933.000000,180000.000000<br>
4.000000,3.000000,1960.000000,1965.000000,604000.000000<br>
3.000000,2.000000,1680.000000,1987.000000,510000.000000<br>
4.000000,4.500000,5420.000000,2001.000000,1230000.000000<br>
3.000000,2.250000,1715.000000,1995.000000,257500.000000<br>

### Structure of the test data file

The first line in the test file should be an integer that provides the number of test data in the file. The rest of the file should be the test data, which should all be comma separated floating point values

An example test data file is shown below:

2<br>
3.000000,2.500000,3560.000000,1965.000000<br>
2.000000,1.000000,1160.000000,1942.000000<br>

*For a detailed look at linear regression, refer to this video:* https://www.youtube.com/watch?v=FIbVs5GbBlQ&hd=1


