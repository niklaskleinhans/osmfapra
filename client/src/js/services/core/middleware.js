import * as coreActions from './actions'
import * as mqttActions from '../mqtt/actions'
import * as mapActions from '../map/actions'
import * as helpers from '../../helpers'


const axios = require('axios');

const coreMiddleware = (function(){
    return store => next => action => {
        switch(action.type){
            case 'SET_NAME':
                action.payload= action.payload + "ze"
                next(action)
                break;

            case 'GET_SERVERINFO':
                axios({
                    method: 'get',
                    url: '/getserverinfo'
                }).then((res)=>{
                    action.payload = {
                        nodecount: parseInt(res.data.nodecount),
                        edgecount: parseInt(res.data.edgecount),
                        importtime: parseInt(res.data.timeForImport)
                    }
                    next(action)
                }).catch(e =>{
                    console.log(e)
                })
                break;

            case 'CREATE_NOTIFICATION':

                // start a timeout to close this notification
                if (!action.notification.sticky){
                    var timeout = setTimeout(
                        function(){
                            store.dispatch(coreActions.closeNotification(action.notification.key))
                        },
                        action.notification.duration * 1000
                    )
                }

                next(action);
                break;

            case 'CLOSE_NOTIFICATION':
                var notifications = Object.assign({}, store.getState().core.notifications);

                // start a timeout to remove this notification
                // This gives us time to animate out the notification before we remove the data
                var timeout = setTimeout(
                    function(){
                        store.dispatch(coreActions.removeNotification(action.key))
                    },
                    200
                )

                next(action);
                break;

            case 'REMOVE_NOTIFICATION':

                // Manual removal
                if (action.manual){
                    var notifications = Object.assign({}, store.getState().ui.notifications);

                    // If a broadcast, add to suppressed_broadcasts
                    if (notifications[action.key] && notifications[action.key].type == 'broadcast'){
                        store.dispatch({
                            type: 'SUPPRESS_BROADCAST',
                            key: action.key
                        })
                    }
                }

                next(action);
                break;
            case 'GENERATE_SHARE_LINK':
                var sharelinkkey = Math.random().toString(36).substr(2, 16);
                store.dispatch(mqttActions.generateShareLinkListener(sharelinkkey))
                action.sharelink = window.location.href + 'sharelocation'+ '/'+ sharelinkkey
                next(action)
                break;
            case 'GET_ROUTE_BY_COORDINATE':
                if (!store.getState().core.routeonrequest){
                    var coordinates = {
                            "srcLongitude" : store.getState().map.friendCoordinates[1], 
                            "srcLatitude" : store.getState().map.friendCoordinates[0], 
                            "trgLongitude" : store.getState().map.currentCoordinates[1], 
                            "trgLatitude" : store.getState().map.currentCoordinates[0],
                            "algorithm" : store.getState().core.algorithm
                        }
                    if (store.getState().map.route.nodes){
                        var nodes = store.getState().map.route.nodes.slice(0,300)

                        // choose node on Path if distance between nearest Pathnode and new node is smaller then epsilon(in meters)
                        var epsilon = store.getState().core.config.epsilonDistancePath
                        var selectedPosition = helpers.getPositionByEpsilonDistance(store.getState().map.friendCoordinates,nodes,epsilon)

                        coordinates.srcLatitude = selectedPosition[0]
                        coordinates.srcLongitude = selectedPosition[1]
                    }
                    //console.log(coordinates)
                    //console.log(selectedPosition)
                    action.routeonrequest = true

                    axios({
                        method: 'post',
                        url: '/routebycoordinate',
                        data: coordinates
                    }).then((res)=>{
                        action.routeonrequest = false
                        store.dispatch(mapActions.storeRoute(res.data))
                        next(action)
                    }).catch(e =>{
                        action.routeonrequest = false
                        console.log(e)
                        next(action)
                    })
                next(action)
                }
                break;
            default:
                return next(action)
        }
    }
})();

export default coreMiddleware