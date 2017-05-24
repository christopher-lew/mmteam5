"""
Created on 03/25/2017
Python 3.6.1

@author: Javier

This script will:
"""

import numpy as np
import matplotlib.pyplot as plt

import IR_Datasets



def isFloat(value):
    """ Function to check if string is a float """
    try:
        float(value)
        return True
    except ValueError:
        return False


def getLists(dataset):
    """
    Creates a list of all the distance values contained inside the keyList.
    Returns this as a sorted list of floats.
    """
    keyList = list(dataset.keys())
    
    distanceList = []
    for key in keyList:
        if(isFloat(key)):
            distanceList.append(float(key))
    distanceList = sorted(distanceList)
    
    readingsList = [];
    for dist in distanceList:
        readingsList.append(dataset[str(dist)])
        
    return distanceList, readingsList


def getRegressionCoeff(dataset, minPolyOrder=-3, maxPolyOrder=3):
    """
    Performs linear regression to calculate the coefficients of the polynomial.
    Args:
        dataset: 
        minPolyOrder: 
        maxPolyOrder:
    Returns:
        coeff:
    """
    # Get the distance and readings list
    [distanceList, readingsList] = getLists(dataset)
    
    # Convert the lists to ndarrays and reshape them to be Nx1 (column) vectors
    N = len(distanceList)
    y = np.asarray(distanceList).reshape((N,1))
    x = np.asarray(readingsList).reshape((N,1))
    
    # Create domain matrix ranging from minPolyOrder to maxPolyOrder
    X = np.power(x, minPolyOrder)
    for polyOrder in range(minPolyOrder+1, maxPolyOrder+1):
        X = np.append(X, np.power(x, polyOrder), axis=1)

    # Find the pseudoinverse to get the coefficients
    A = np.dot(np.transpose(X), X)
    B = np.dot(np.transpose(X), y)
    coeff = np.linalg.lstsq(A, B)[0]

    return coeff


def genBestFitPoly(coeff, dataset, minPolyOrder=-3, maxPolyOrder=3):
    # Get the distance and readings list and round to 2 decimal points
    [_, readingsList] = getLists(dataset)
    maxRead = round(readingsList[0], 2)
    minRead = round(readingsList[-1], 2) 
    
    yRange = np.arange(minRead, maxRead, 0.01)
    xRange = []
    for y in yRange:
        x = 0.0
        i = 0
        for p in range(minPolyOrder, maxPolyOrder+1):
            x += coeff[i,0] * (y**p)    # ** == ^ in python 3
            i += 1
            
        xRange.append(x)
    
    return [np.array(xRange), yRange]
    
    
def plot_datasetVSbestFit(dataset, gen_xRange, gen_yRange):   
    [distanceList, readingsList] = getLists(dataset)
    plt.plot(distanceList, readingsList, 'rx')
    plt.plot(gen_xRange, gen_yRange, 'b')
    plt.xlabel('Distance (cm)')
    plt.ylabel('ADC Value')
    plt.show()
    


if __name__ == '__main__':
    dataset = IR_Datasets.get_dataset()
    
    coeff = getRegressionCoeff(dataset)
    
    [gen_xRange, gen_yRange] = genBestFitPoly(coeff, dataset)
    
    plot_datasetVSbestFit(dataset, gen_xRange, gen_yRange)

    