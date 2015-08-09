# PCM: A Pairwise Correlation Mining Package
------ 
One fundamental task in molecular biology is to understand the dependency among genes or proteins to model
biological networks. Numerous methods have been developed for reconstructing different types of networks using data sets generated from high-throughput technologies. 

we provide PCM, an opensource implementation of pairwise correlation mining algorithms supporting many widely used marginal correlation measures, and additionally provide several algorithms for calculating low-order conditional correlations.

PCM was implemented in C++, which uses a table as input. Columns and rows in the input table correspond to variables (e.g. genes, proteins) and samples (e.g. gene expression profiles), respectively.

In the current version, PCM contains 11 correlation measures for continuous variables and 27 correlation
measures for binary variables. We also provide many interfaces for users.

## Usage
If you want to find all protein pairs whose Pearson¡¯s correlation coefficients are no less than 0.2 from the example data and put the mining results into the file ¡°output.txt¡±, we can use the following commands:
          
          PCM.exe PearsonC data.txt output.txt 0.2 
  
If you want to use the algorithm LOPC in Zuo et al. (2014) obtain only pairs whose conditional correlation coefficients (from 0th order up to 2nd order) are significant enough, the following commands we can use:
            
          PCM.exe LOPCC data.txt output.txt

The more usages can be found in  0.1.0_doucument.pdf.  

