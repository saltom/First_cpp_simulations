#!/usr/bin/env python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df_var = pd.read_csv('data_var.txt', header = None, names=['t', 'var1', 'var2'])
t = df_var['t']
var1 = df_var['var1']
var2 = df_var['var2']

df_corr = pd.read_csv('data_corr.txt', header = None, names=['t', 'corr1', 'corr2'])
corr1 = df_corr['corr1']
corr2 = df_corr['corr2']

df_cross = pd.read_csv('data_cross.txt', header = None, names=['tau','cross'])
tau = df_cross['tau']
cross = df_cross['cross']

font = 18
ticks = 15
width = 2
size = (6,4)

fig, ax = plt.subplots(figsize=size)
plt.subplots_adjust(left=0.2, right=0.9, top=0.9, bottom=0.2)
ax.tick_params(axis='x', labelsize=ticks) 
ax.tick_params(axis='y', labelsize=ticks) 
ax.set_xlabel('Time', fontsize=font)
ax.set_ylabel('Variance', fontsize=font)
ax.plot(t, var1, color='green', lw=width)
ax.plot(t, var2, color='orange', lw=width)
fig.savefig('var.pdf')

fig, ax = plt.subplots(figsize=size)
plt.subplots_adjust(left=0.2, right=0.9, top=0.9, bottom=0.2)
ax.tick_params(axis='x', labelsize=ticks) 
ax.tick_params(axis='y', labelsize=ticks) 
ax.set_xlabel('Time', fontsize=font)
ax.set_ylabel('Correlation', fontsize=font)
ax.plot(t, corr1, color='green', lw=width)
ax.plot(t, corr2, color='orange', lw=width)
fig.savefig('corr.pdf')

fig, ax = plt.subplots(figsize=size)
plt.subplots_adjust(left=0.2, right=0.9, top=0.9, bottom=0.2)
ax.tick_params(axis='x', labelsize=ticks) 
ax.tick_params(axis='y', labelsize=ticks) 
ax.set_xlabel('Time', fontsize=font)
ax.set_ylabel('Correlation', fontsize=font)
ax.plot(tau, cross, color='green', lw=width)
fig.savefig('cross.pdf')




