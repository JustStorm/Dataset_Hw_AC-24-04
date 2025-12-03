import pandas as pd
import time
import pathlib

# 
# НАЧАЛО НАСТРОЕК
# 

# Кол-во строк
read_amount = 1_000

inputfile = 'US_Accidents_March23.csv'
# inputfile = 'small.csv'

# outfile = 'output.csv'
outfile = f'Accidents_{read_amount // 1000}k.csv'

# 
# КОНЕЦ НАСТРОЕК
# 

datasets = pathlib.Path(__file__).parent / 'dataset'

removing_columns = {'ID','Source','Start_Time','End_Time',
                    'Start_Lat','Start_Lng','End_Lat','End_Lng',
                    'Distance(mi)','Description','Street','Zipcode',
                    'Country','Timezone','Airport_Code','Weather_Timestamp',
                    'Visibility(mi)','Wind_Direction','Precipitation(in)',
                    'Amenity','Bump','Crossing','Give_Way','Junction',
                    'No_Exit','Railway','Roundabout','Station','Stop',
                    'Traffic_Calming','Traffic_Signal','Turning_Loop','Sunrise_Sunset',
                    'Civil_Twilight','Nautical_Twilight','Astronomical_Twilight'}

a = time.time()
data = pd.read_csv(datasets / inputfile, nrows=read_amount)
b = time.time()


print(f'Reading finished! Took {round(b-a,2)}s')

for column_name in removing_columns:
    data = data.drop(column_name, axis=1)

print('Processing finished!')
data.info()

data.to_csv(datasets / outfile, index_label='ID')


print('Saved to new CSV!')
