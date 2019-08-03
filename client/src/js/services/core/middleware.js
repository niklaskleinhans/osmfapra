import * as coreActions from './actions'

const coreMiddleware = (function(){
    return store => next => action => {
        switch(action.type){
            case 'SET_NAME':
                action.payload= action.payload + "ze"
                next(action)
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
            default:
                return next(action)
        }
    }
})();

export default coreMiddleware