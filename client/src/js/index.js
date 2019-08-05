import React from 'react';
import ReactDOM from 'react-dom';
import {Provider} from 'react-redux'
import {Router, Route, Switch} from 'react-router'
import createHistory from 'history/createBrowserHistory';

import App from './App';
import Home from './views/Home'
import ShareLocation from './views/ShareLocation'

import store from './bootstrap'
import * as serviceWorker from './serviceWorker';
require('../scss/App.scss')

global.baseURL = '/'

//const history = syncHistoryWithStore(browserHistory, store)
const history = createHistory()

ReactDOM.render(
    <Provider store={store}>
        <Router history = {history}>
            <Switch>
                <Route exact path="/" component={App}/>
                <Route path="/ShareLocation/:sharekey" component={ShareLocation}/>
            </Switch>
        </Router>
    </Provider>, 
    document.getElementById('root'));

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: http://bit.ly/CRA-PWA
serviceWorker.unregister();
