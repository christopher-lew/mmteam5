"""
Created on 05/24/2017
Python 3.5.3

@author: Javier

This script will parse pid data output by the Falcon.
"""

import numpy as np
import matplotlib.pyplot as plt


separatorString = "##### ##### #####"
curTrialFile = "pid_data/currentTrial.txt"


def read_trial_header(file):
    headerData = {}
    for i in range(5):
        line = file.readline().split("=")
        headerData[line[0].strip()] = float(line[1].strip())
    return headerData


def read_trial_data(file):
    header = read_trial_header(file)    
    n_samples = int(header['Samples'])
    print_args = int(header['Args'])
    
    errorP_log = []
    errorD_log = []
    leftDist_log = []
    rightDist_log = []
    data = {}

    if (print_args == 2):
        for i in range(n_samples):
            line = file.readline().split(",")
            errorP_log.append(float(line[0].strip()))
            errorD_log.append(float(line[1].strip()))
            
        errorP = np.array(errorP_log)
        errorD = np.array(errorD_log)
        data = {'header':header, 'errorP':errorP, 'errorD':errorD}
    
    elif (print_args == 4):
        for i in range(n_samples):
            line = file.readline().split(",")
            errorP_log.append(float(line[0].strip()))
            errorD_log.append(float(line[1].strip()))
            leftDist_log.append(float(line[2].strip()))
            rightDist_log.append(float(line[3].strip()))
            
        errorP = np.array(errorP_log)
        errorD = np.array(errorD_log)
        leftDist = np.array(leftDist_log)
        rightDist = np.array(rightDist_log)
        data = {'header':header, 'errorP':errorP, 'errorD':errorD, 'leftDist':leftDist, 'rightDist':rightDist}
    
    return data


if __name__ == '__main__':
    allData = []
    with open(curTrialFile, 'r') as file:
        while (separatorString in file.readline()):
            allData.append(read_trial_data(file))
            
    # Plot data from all separate trials
    i = 1
    n_trials = len(allData)   
    print_args = int(allData[0]['header']['Args'])
    
    if (print_args == 2):
        n_graphs = 3
        plt.figure(1)
        plt.suptitle("PID Error Graphs", fontsize=20)
        plt.subplots_adjust(hspace=0.7)     # Adjust space between subplots
        plt.subplots_adjust(wspace=0.3)
        
        for trial in allData:
            header = trial['header']
            errorP = trial['errorP'] * header['Kp']
            errorD = trial['errorD'] * header['Kd']
            totalError = errorP + errorD
            
            xData = np.arange(int(header['Samples']))
            xData = xData * header['Period'] * 1000
            
            plt.subplot(n_trials, n_graphs, i)
            plt.plot(xData, errorP)
            plt.xlabel('Time (ms)')
            plt.ylabel('Error P')
            plt.title('Kp = {}'.format(header['Kp']))
            plt.grid(True)
            
            plt.subplot(n_trials, n_graphs, i+1)
            plt.plot(xData, errorD)
            plt.xlabel('Time (ms)')
            plt.ylabel('Error D')
            plt.title('Kd = {}'.format(header['Kd']))
            plt.grid(True)
            
            plt.subplot(n_trials, n_graphs, i+2)
            plt.plot(xData, totalError)
            plt.xlabel('Time (ms)')
            plt.ylabel('Total Error')
            plt.grid(True)
            
            i += n_graphs
        
    elif (print_args == 4):
        n_graphs = 4
        plt.figure(1)
        plt.suptitle("PID Error Graphs", fontsize=20)
        plt.subplots_adjust(hspace=0.7)     # Adjust space between subplots
        plt.subplots_adjust(wspace=0.3)
        
        for trial in allData:
            header = trial['header']
            errorP = trial['errorP'] * header['Kp']
            errorD = trial['errorD'] * header['Kd']
            leftDist = trial['leftDist']
            rightDist = trial['rightDist']
            avgDist = (leftDist + rightDist) / 2.0
            totalError = errorP + errorD
            
            xData = np.arange(int(header['Samples']))
            xData = xData * header['Period'] * 1000
                                  
            plt.subplot(n_trials, n_graphs, i)
            plt.plot(xData, leftDist,'g')
            plt.plot(xData, rightDist,'b')
            plt.plot(xData, avgDist,'r')
            plt.xlabel('Time (ms)')
            plt.ylabel('Distance (cm)')
            plt.title('Left (G), Right(B), and Avg(R) Dist')
            plt.grid(True)
            
            plt.subplot(n_trials, n_graphs, i+1)
            plt.plot(xData, errorP)
            plt.xlabel('Time (ms)')
            plt.ylabel('Error P')
            plt.title('Kp = {}'.format(header['Kp']))
            plt.grid(True)
            
            plt.subplot(n_trials, n_graphs, i+2)
            plt.plot(xData, errorD)
            plt.xlabel('Time (ms)')
            plt.ylabel('Error D')
            plt.title('Kd = {}'.format(header['Kd']))
            plt.grid(True)
            
            plt.subplot(n_trials, n_graphs, i+3)
            plt.plot(xData, totalError)
            plt.xlabel('Time (ms)')
            plt.ylabel('Total Error')
            plt.grid(True)
            
            i += n_graphs