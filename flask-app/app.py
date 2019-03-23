from datetime import datetime
from flask import Flask, request
from flask_restplus import Api, Resource, fields
import json
import logging
import time
from pytz import timezone, utc
import redis
import json
import datetime

app = Flask(__name__)
api = Api(app, version='1.0', title='rinkMonitor API',
    description='Monitor remote sensors.',
)

logger = app.logger

ns = api.namespace('sensors', description='Info collected by remote sensors')

REDIS_HOST = 'redis'
REDIS_PORT = '6379'
REDIS_CONN = redis.Redis(host=REDIS_HOST, port=REDIS_PORT)

class sensorDAO(object):
    def get_sensor_list(self):
        sensors = []
        bytes = REDIS_CONN.get('sensors')
        if bytes is not None:
            sensors = json.loads(bytes.decode('utf-8'))
        else:
            REDIS_CONN.set('sensors',json.dumps(sensors))
        return sensors
    
    def get_all(self):
        sensors = self.get_sensor_list()
        sensor_data = {}
        
        for sensor in sensors:
            sensor_bytes = REDIS_CONN.get(sensor)
            if sensor_bytes is not None:
                sensor_data[sensor] = json.loads(sensor_bytes.decode('utf-8'))
                
        # print(door_data)
            
        return sensor_data
        api.abort(404, "Could not find any sensors.".format(id))
        
    def get(self, id):
        bytes = REDIS_CONN.get(id)
        if bytes is not None:
            sensor = json.loads(bytes.decode('utf-8'))

            return sensor
        api.abort(404, "Sensor {} doesn't exist.".format(id))

    def create(self, id, data):
        sensor_list = self.get_sensor_list()
        if id in sensor_list:
            print('Sensor {} already exists.  Doing nothing.'.format(id))
        else:
            sensor_list.append(id)
            REDIS_CONN.set('sensors',json.dumps(sensor_list))
            
            assert REDIS_CONN.set(id,json.dumps(data)) == True
        
        return id

    def update(self, id, data):
        bytes = REDIS_CONN.get(id)
        if bytes is not None:
            sensor = json.loads(bytes.decode('utf-8'))
            
        if isinstance(data.decode('utf-8'), str):
            sensor['reading'] = data.decode('utf-8')
            sensor['last_updated'] = datetime.datetime.now().isoformat()

            assert REDIS_CONN.set(id,json.dumps(sensor)) == True

            return sensor
        else:
            return 'no_data'

    def delete(self, id):
        sensor_list = self.get_sensor_list()
        sensor_list.remove(id)
        assert REDIS_CONN.set('sensors',json.dumps(sensor_list)) == True
        assert REDIS_CONN.delete(id) == True
        
        
DAO = sensorDAO()
DAO.create('probe_1_temp',{'reading': 'unknown', 'last_updated':None})

DAO.create('dht_1_temp',{'reading': 'unknown', 'last_updated':None})
DAO.create('dht_1_hum',{'reading': 'unknown', 'last_updated':None})

DAO.create('dht_2_temp',{'reading': 'unknown', 'last_updated':None})
DAO.create('dht_2_hum',{'reading': 'unknown', 'last_updated':None})

DAO.create('dht_3_temp',{'reading': 'unknown', 'last_updated':None})
DAO.create('dht_3_hum',{'reading': 'unknown', 'last_updated':None})

DAO.create('dht_4_temp',{'reading': 'unknown', 'last_updated':None})
DAO.create('dht_4_hum',{'reading': 'unknown', 'last_updated':None})


@ns.route('/')
class AllSensorData(Resource):
    '''Shows a list of all sensor data and lets you POST to add new sensors'''
    @ns.doc('list_sensors')
    def get(self):
        '''List all sensor data.'''
        sensor_info = DAO.get_all()

        return sensor_info
    
    
@ns.route('/<id>')
@ns.response(404, 'Sensor not found')
@ns.param('id', 'The sensor identifier')
class SensorInfo(Resource):
    '''Show a single sensor item and lets you delete them'''
    def get(self, id):
        '''Fetch a given resource'''
        return DAO.get(id)

    def put(self, id):
        '''Update a sensor given its identifier'''
        logger.info(request.data)
        return DAO.update(id, request.data)
    
    def delete(self, id):
        '''Delete a sensor given its identifier'''
        return DAO.delete(id)