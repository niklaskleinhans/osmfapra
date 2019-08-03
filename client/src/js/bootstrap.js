import {createStore, applyMiddleware, combineReducers} from 'redux';
import geoMiddleware from 'redux-effects-geolocation';
import * as helpers from './helpers'
import thunk from 'redux-thunk'
import { composeWithDevTools } from 'redux-devtools-extension/developmentOnly';

import core from './services/core/reducer'
import mqtt from './services/mqtt/reducer'
import coreMiddleware from './services/core/middleware'
import mqttMiddleware from './services/mqtt/middleware'

let reducers = combineReducers({
    core,
    mqtt
});


let initialState = {
    core:{
        name : 'NIXDA'
    },
    mqtt:{

    },
    notifications: {}
}

initialState.core = Object.assign({}, initialState.core, helpers.getStorage('core'))
initialState.mqtt = Object.assign({}, initialState.mqtt, helpers.getStorage('mqtt'))

const composeEnhancers =composeWithDevTools({

});

let store = createStore(
    reducers,
    initialState,
    composeEnhancers(
        applyMiddleware(thunk, geoMiddleware(), coreMiddleware, mqttMiddleware)
    )
)

export default store;