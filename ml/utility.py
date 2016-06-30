#!/usr/bin/python

import pandas as pd
import seaborn as sns

def sns_regplot_table(table, str_x, str_y, image):
    plot = sns.regplot(x=str_x, y=str_y, data=table)
    fig = plot.get_figure()
    fig.savefig(image)

def sns_regplot_file(csv, str_x, str_y, image):
    df = pd.read_csv(csv)
    columns = [str_x, str_y]
    df1 = df[columns]
    plot = sns.regplot(x=str_x, y=str_y, data=df1)
    fig = plot.get_figure()
    fig.savefig(image)

