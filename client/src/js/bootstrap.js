import {createStore, applyMiddleware, combineReducers} from 'redux';
import geoMiddleware from 'redux-effects-geolocation';
import * as helpers from './helpers'
import thunk from 'redux-thunk'
import { composeWithDevTools } from 'redux-devtools-extension/developmentOnly';
//import { composeWithDevTools } from 'redux-devtools-extension/';

import { routerReducer } from 'react-router-redux'
import core from './services/core/reducer'
import map from './services/map/reducer'
import mqtt from './services/mqtt/reducer'
import coreMiddleware from './services/core/middleware'
import mapMiddleware from './services/map/middleware'
import mqttMiddleware from './services/mqtt/middleware'

let reducers = combineReducers({
    core,
    map,
    mqtt,
    routing: routerReducer
});


let initialState = {
    core:{
        name : 'NIXDA',
        sidebar_open: true,
        servinfo_open: false,
        routeonrequest : false,
        serverinfo:{
            nodecount:0,
            edgecount:0,
            importtime:0,
        }
    },
    mqtt:{

    },
    notifications: {},
    map:{
        route:{}
    }
}

initialState.core = Object.assign({}, initialState.core, helpers.getStorage('core'))
initialState.mqtt = Object.assign({}, initialState.mqtt, helpers.getStorage('mqtt'))
initialState.map = Object.assign({}, initialState.map, helpers.getStorage('map'))

const composeEnhancers =composeWithDevTools({

});

let store = createStore(
    reducers,
    initialState,
    composeEnhancers(
        applyMiddleware(thunk, geoMiddleware(), coreMiddleware,mapMiddleware, mqttMiddleware)
    )
)

export default store;