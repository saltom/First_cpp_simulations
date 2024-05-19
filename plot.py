#!/usr/bin/env python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df_var = pd.read_csv('data_var.txt', header = None, names=['t', 'var'])
t = df_var['t']
var = df_var['var']

df_corr = pd.read_csv('data_corr.txt', header = None, names=['t', 'corr'])
corr = df_corr['corr']

n = np.linspace(100, 1000, 10)

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
ax.plot(t, var, color='green', lw=width)
fig.savefig('var.pdf')

fig, ax = plt.subplots(figsize=size)
plt.subplots_adjust(left=0.2, right=0.9, top=0.9, bottom=0.2)
ax.tick_params(axis='x', labelsize=ticks) 
ax.tick_params(axis='y', labelsize=ticks) 
ax.set_xlabel('Time', fontsize=font)
ax.set_ylabel('Correlation', fontsize=font)
ax.plot(t, corr, color='green', lw=width)
fig.savefig('corr.pdf')
