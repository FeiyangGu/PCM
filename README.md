# PCM: A Pairwise Correlation Mining Package for Biological Network Inference
------ 
One fundamental task in molecular biology is to understand the dependency among genes or proteins to model biological networks. Numerous methods have been developed for reconstructing different types of networks using data sets generated from high-throughput technologies. 

We provide PCM, an opensource implementation of pairwise correlation mining algorithms supporting many widely used marginal correlation measures, and additionally provide several algorithms for calculating low-order conditional correlations.

PCM was implemented in C++, which uses a table as input. Columns and rows in the input table correspond to variables (e.g. genes, proteins) and samples (e.g. gene expression profiles), respectively. The source code are stored in PCM_CODE folder. The fold named eigen in it is the library eigen.

In the current version, PCM contains 11 correlation measures for continuous variables and 27 correlation measures for binary variables. Since it is very time-consuming to perform the pairwise
correlation mining when the number of variables is very large, we also provide a fast algorithm for generating an approximate set of correlated pairs. This algorithm first uses clustering algorithms to partition the variables into different clusters, and then calculates the pairs which are only in the same cluster. 

We provide two sample data. One is a network inference data, DREAM3, which has 100 rows and 100 columns.  DREAM3 is a continuous data and is named as data_DREAM3.txt in data file. The other is also a PPI network inference data, Gavin et al. We transform this data to a binary table and name it as data_Gavin.txt in the data file. It contains 2166 rows and 2761 columns. 

## Usage
If you want to find all pairs whose Pearson’s correlation coefficients are no less than 0.2 from the example data and put the mining results into the file “output.txt”, we can use the following command:
          
          PCM PearsonC data_DREAM3.txt output.txt 0.2 
          
To rapidly obtain a set of correlated pairs, we can use the following command:
          
          PCM PearsonC data_DREAM3.txt output.txt 0.2  1  5
          
In this command  1 and 5 means that PCM first uses k-means to partition the variables into 5 clusters, and then calculates the pairs which are only in the same cluster. 


If you want to use the algorithm LOPC in Zuo et al. (2014) obtain only pairs whose conditional correlation coefficients (from 0th order up to 2nd order) are significant enough, the following command we can use:
            
          PCM LOPCC data_DREAM3.txt output.txt

The more usages can be found in  PCM_Document_1.0.0.pdf.  

