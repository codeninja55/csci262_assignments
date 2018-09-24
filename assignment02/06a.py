import pandas as pd
from IPython.display import display, HTML

n_x = 1  # number of X infected computers at t = 0

table = {'Time': [],
         'X': []}

for i in range(0, 25):
    table['Time'].append(i)
    table['X'].append(n_x)
    n_x *= 2

df = pd.DataFrame(table)
display(df)
