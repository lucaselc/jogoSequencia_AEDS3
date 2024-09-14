#!/usr/bin/env python
import sqlite3
import matplotlib.pyplot as plt
import numpy as np

# Connect to the SQLite database
conn = sqlite3.connect('times.db')
cursor = conn.cursor()

# Query to get data from the tables
query = """
SELECT configuration.n, time.user, time.system, time.clock, configuration.strat
FROM time
JOIN configuration ON time.config_id = configuration.id
"""

cursor.execute(query)
data = cursor.fetchall()

# Close the connection
conn.close()

# Process data
strategies = {}
for row in data:
    n, user, system, clock, strat = row
    if strat not in strategies:
        strategies[strat] = {'n': [], 'user': [], 'system': [], 'clock': []}
    strategies[strat]['n'].append(n)
    strategies[strat]['user'].append(user)
    strategies[strat]['system'].append(system)
    strategies[strat]['clock'].append(clock)

# Function to aggregate data by 'n' and calculate averages
def aggregate_data(n_list, time_list):
    n_dict = {}
    for n, time in zip(n_list, time_list):
        if n not in n_dict:
            n_dict[n] = []
        n_dict[n].append(time)
    n_values = sorted(n_dict.keys())
    avg_times = [np.mean(n_dict[n]) for n in n_values]
    return n_values, avg_times

# Plot data for each strategy
for strat, times in strategies.items():
    n_values, user_avg = aggregate_data(times['n'], times['user'])
    _, system_avg = aggregate_data(times['n'], times['system'])
    _, clock_avg = aggregate_data(times['n'], times['clock'])

    plt.figure(figsize=(10, 6))
    plt.plot(n_values, user_avg, label='Tempo de Usuário', marker='o')
    plt.plot(n_values, system_avg, label='Tempo de Sistema', marker='o')
    plt.plot(n_values, clock_avg, label='Tempo de Relógio', marker='o')

    # Adding labels and title
    plt.xlabel('Tamanho das Entradas (n)')
    plt.ylabel('Tempo médio')
    plt.title(f'Tempo médio pelo Número de Entradas ({strat})')
    plt.legend()
    plt.grid(True)

    # Show plot
    plt.savefig(f'img/{strat}.svg')

