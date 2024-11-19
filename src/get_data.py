import requests
import sys
import json
import os
import shutil


def main(key, symbol):
    url = f'https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol={symbol}&apikey={key}'
    r = requests.get(url)
    data = r.json()
    with open(symbol+'.json', 'w') as f:
        json.dump(data, f)
    
    _p = os.getcwd()
    destination_file = os.path.join("../fetched_data", os.path.basename(symbol+".json"))
    shutil.move(symbol+".json", destination_file)
    return 0

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
