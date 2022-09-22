import numpy as np
from sklearn import preprocessing
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from sklearn.manifold import MDS
import pandas as pd
import matplotlib.pyplot as plt

def normalize(df):
    x = df.values
    min_max_scaler = preprocessing.MinMaxScaler()
    x_scaled = min_max_scaler.fit_transform(x)
    df = pd.DataFrame(x_scaled)
    return df

def invert_response(n):
    if n == 1:
        n = 5
    elif n == 2:
        n = 4
    elif n == 3:
        n = 3
    elif n == 4:
        n = 1
    elif n == 5:
        n = 1
    else:
        n = 3
    return n

extroversion = ['E1', 'E2', 'E3', 'E4', 'E5', 'E6', 'E7', 'E8', 'E9', 'E10']
neuroticism = ['N1', 'N2', 'N3', 'N4', 'N5', 'N6', 'N7', 'N8', 'N9', 'N10']
agreeableness = ['A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8', 'A9', 'A10']
conscientiousness = ['C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8', 'C9', 'C10']
openness = ['O1', 'O2', 'O3', 'O4', 'O5', 'O6', 'O7', 'O8', 'O9', 'O10']
all_responses = ['E1', 'E2', 'E3', 'E4', 'E5', 'E6', 'E7', 'E8', 'E9', 'E10', 'N1', 'N2', 'N3', 'N4', 'N5', 'N6', 'N7', 'N8', 'N9', 'N10', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8', 'A9', 'A10', 'C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8', 'C9', 'C10', 'O1', 'O2', 'O3', 'O4', 'O5', 'O6', 'O7', 'O8', 'O9', 'O10']

full_df = pd.read_csv('data.tsv', sep = '\t', index_col = None, low_memory = False)
full_df.columns = ['race', 'age', 'engnat', 'gender', 'hand', 'source', 'country', 'E1', 'E2', 'E3', 'E4', 'E5', 'E6', 'E7', 'E8', 'E9', 'E10', 'N1', 'N2', 'N3', 'N4', 'N5', 'N6', 'N7', 'N8', 'N9', 'N10', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8', 'A9', 'A10', 'C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'C8', 'C9', 'C10', 'O1', 'O2', 'O3', 'O4', 'O5', 'O6', 'O7', 'O8', 'O9', 'O10']
full_df['E2'] = full_df['E2'].apply(invert_response)
full_df['E4'] = full_df['E4'].apply(invert_response)
full_df['E6'] = full_df['E6'].apply(invert_response)
full_df['E8'] = full_df['E8'].apply(invert_response)
full_df['E10'] = full_df['E10'].apply(invert_response)
full_df['N2'] = full_df['N2'].apply(invert_response)
full_df['N4'] = full_df['N4'].apply(invert_response)
full_df['A1'] = full_df['A1'].apply(invert_response)
full_df['A3'] = full_df['A3'].apply(invert_response)
full_df['A5'] = full_df['A5'].apply(invert_response)
full_df['A7'] = full_df['A7'].apply(invert_response)
full_df['C2'] = full_df['C2'].apply(invert_response)
full_df['C4'] = full_df['C4'].apply(invert_response)
full_df['C6'] = full_df['C6'].apply(invert_response)
full_df['C8'] = full_df['C8'].apply(invert_response)
full_df['O2'] = full_df['O2'].apply(invert_response)
full_df['O4'] = full_df['O4'].apply(invert_response)
full_df['O6'] = full_df['O6'].apply(invert_response)

ext_df = full_df[extroversion]
neuro_df = full_df[neuroticism]
agree_df = full_df[agreeableness]
consc_df = full_df[conscientiousness]
open_df = full_df[openness]

all_responses_df = full_df[all_responses]

pca = PCA(n_components = 2)
consc_pcs = pca.fit_transform(consc_df)
consc_pca_df = pd.DataFrame(data = consc_pcs, columns = ['pc1','pc2'], index = full_df['age'].values)

consc_age_plot = plt.figure(1, figsize = (10,10))
plt.scatter(consc_pca_df['pc1'], consc_pca_df['pc2'], 1, 
color = ['blue' if x > 12 and x < 27 
else 'red' if x >= 27 and x < 35
else 'green' if x >= 35 and x < 50
else 'purple' if x >= 50 and x < 65
else 'orange' if x >= 65
else 'magenta' for x in consc_pca_df.index])
consc_age_plot.suptitle('conscientiousness by age')

pca = PCA(n_components = 2)
open_pcs = pca.fit_transform(open_df)
open_pca_df = pd.DataFrame(data = open_pcs, columns = ['pc1','pc2'], index = full_df['age'].values)

open_age_plot = plt.figure(2, figsize = (10,10))
plt.scatter(open_pca_df['pc1'], open_pca_df['pc2'], 1, 
color = ['blue' if x > 12 and x < 27 
else 'red' if x >= 27 and x < 35
else 'green' if x >= 35 and x < 50
else 'purple' if x >= 50 and x < 65
else 'orange' if x >= 65
else 'magenta' for x in open_pca_df.index])
open_age_plot.suptitle('openness by age')

pca = PCA(n_components = 2)
neuro_pcs = pca.fit_transform(neuro_df)
neuro_pca_df = pd.DataFrame(data = neuro_pcs, columns = ['pc1','pc2'], index = full_df['age'].values)

neuro_age_plot = plt.figure(3, figsize = (10,10))
plt.scatter(neuro_pca_df['pc1'], neuro_pca_df['pc2'], 1, 
color = ['blue' if x > 12 and x < 27 
else 'red' if x >= 27 and x < 35
else 'green' if x >= 35 and x < 50
else 'purple' if x >= 50 and x < 65
else 'orange' if x >= 65
else 'magenta' for x in neuro_pca_df.index])
neuro_age_plot.suptitle('neuroticism by age')

pca = PCA(n_components = 2)
agree_pcs = pca.fit_transform(agree_df)
agree_pca_df = pd.DataFrame(data = agree_pcs, columns = ['pc1','pc2'], index = full_df['age'].values)

agree_age_plot = plt.figure(4, figsize = (10,10))
plt.scatter(agree_pca_df['pc1'], agree_pca_df['pc2'], 1, 
color = ['blue' if x > 12 and x < 27 
else 'red' if x >= 27 and x < 35
else 'green' if x >= 35 and x < 50
else 'purple' if x >= 50 and x < 65
else 'orange' if x >= 65
else 'magenta' for x in agree_pca_df.index])
agree_age_plot.suptitle('agreeableness by age')

pca = PCA(n_components = 2)
ext_pcs = pca.fit_transform(ext_df)
ext_pca_df = pd.DataFrame(data = ext_pcs, columns = ['pc1','pc2'], index = full_df['age'].values)

ext_age_plot = plt.figure(5, figsize = (10,10))
plt.scatter(ext_pca_df['pc1'], ext_pca_df['pc2'], 1, 
color = ['blue' if x > 12 and x < 27 
else 'red' if x >= 27 and x < 35
else 'green' if x >= 35 and x < 50
else 'purple' if x >= 50 and x < 65
else 'orange' if x >= 65
else 'magenta' for x in ext_pca_df.index])
ext_age_plot.suptitle('extroversion by age')

plt.show()