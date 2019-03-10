import {createStore, applyMiddleware, combineReducers} from 'redux';
import * as helpers from './helpers'
import thunk from 'redux-thunk'
import { composeWithDevTools } from 'redux-devtools-extension/developmentOnly';

let reducers = combineReducers({
});


let initialState = {
}

initialState.core = Object.assign({}, initialState.core, helpers.getStorage('core'))

const composeEnhancers =composeWithDevTools({

});

let store = createStore(
    reducers,
    initialState,
    composeEnhancers(
        applyMiddleware(thunk)
    )
)

export default store;