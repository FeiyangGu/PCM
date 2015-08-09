# PCM: A Pairwise Correlation Mining Package
------ 
One fundamental task in molecular biology is to understand the dependency among genes or proteins to model
biological networks. Numerous methods have been developed for reconstructing different types of networks using data sets generated from high-throughput technologies. 

We provide PCM, an opensource implementation of pairwise correlation mining algorithms supporting many widely used marginal correlation measures, and additionally provide several algorithms for calculating low-order conditional correlations.

PCM was implemented in C++, which uses a table as input. Columns and rows in the input table correspond to variables (e.g. genes, proteins) and samples (e.g. gene expression profiles), respectively. The source code are stored in PCM_CODE folder and the fold named eigen in it is the library eigen.

In the current version, PCM contains 11 correlation measures for continuous variables and 27 correlation
measures for binary variables. We also provide many interfaces for users. 

We provide two sample data. One is a network inference data, DREAM3, which has 100 rows and 100 columns.  DREAM3 is a continuous data and is named as data_DREAM3.txt in data file. The other is also a PPI network inference data, Gavin et al. We transform this data to a binary table and name it as data_Gavin.txt in the data file. It contains 2166 rows and 2761 columns. 

## Usage
If you want to find all protein pairs whose Pearson’s correlation coefficients are no less than 0.2 from the example data and put the mining results into the file “output.txt”, we can use the following commands:
          
          PCM.exe PearsonC data.txt output.txt 0.2 
  
If you want to use the algorithm LOPC in Zuo et al. (2014) obtain only pairs whose conditional correlation coefficients (from 0th order up to 2nd order) are significant enough, the following commands we can use:
            
          PCM.exe LOPCC data.txt output.txt

The more usages can be found in  0.1.0_doucument.pdf.  

