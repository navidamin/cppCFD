#!/usr/bin/env python
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import pandas as pd
import glob
import os
import sys

def plot_csv(filename, ax, label=None):
    data = pd.read_csv(filename)
    ax.plot(data['x'], data['u'], label=label)
    ax.set_xlabel('x')
    ax.set_ylabel('u')
    time = data['time'].iloc[0]
    ax.set_title(f'Time: {time:.3f}')

def plot_all_results():
    results_dir = 'results'
    plots_dir = 'plots'
    
    # Check if results directory exists
    if not os.path.exists(results_dir):
        print(f"Error: '{results_dir}' directory not found. Please make sure the results are generated before running this script.")
        sys.exit(1)

    # Create plots directory if it doesn't exist
    if not os.path.exists(plots_dir):
        os.makedirs(plots_dir)
    
    # Check for required CSV files
    initial_state = os.path.join(results_dir, 'initial_state.csv')
    final_state = os.path.join(results_dir, 'final_state.csv')
    if not (os.path.exists(initial_state) and os.path.exists(final_state)):
        print(f"Error: Required CSV files not found in '{results_dir}' directory.")
        sys.exit(1)

    # Plot initial and final states
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 10))
    plot_csv(initial_state, ax1, label='Initial State')
    plot_csv(final_state, ax1, label='Final State')
    ax1.legend()
    ax1.set_title('Initial and Final States')

    # Plot intermediate states
    csv_files = sorted(glob.glob(os.path.join(results_dir, 'state_*.csv')))
    if not csv_files:
        print(f"Warning: No intermediate state files found in '{results_dir}' directory.")
    for file in csv_files:
        plot_csv(file, ax2)
    ax2.set_title('Intermediate States')

    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'linear_convection_results.png'))
    plt.close()

    # Plot animation
    fig, ax = plt.subplots(figsize=(8, 6))
    csv_files = [initial_state] + csv_files + [final_state]
    
    # Create animation frames
    for i, file in enumerate(csv_files):
        ax.clear()
        plot_csv(file, ax)
        ax.set_ylim(0.5, 2.5)
        plt.savefig(os.path.join(plots_dir, f'frame_{i:03d}.png'))
    
    plt.close()
    print(f"Plots and animation frames saved in '{plots_dir}' directory.")

if __name__ == "__main__":
    plot_all_results()
