export default function reducer(core = {}, action){
    switch(action.type){
        case 'TOGGLE_SIDEBAR':
                var new_state = !core.sidebar_open
                if (typeof(action.new_state) !== 'undefined' ) new_state = action.new_state
                return Object.assign({}, core, { sidebar_open : new_state })
        case 'TOGGLE_SERVERINFO':
                var new_state = !core.serverinfo_open
                return Object.assign({}, core, { serverinfo_open : new_state })
        case 'CREATE_NOTIFICATION':
            var notifications = Object.assign({}, core.notifications);
            notifications[action.notification.key] = action.notification;
            return Object.assign({}, core, { notifications: notifications });
        case 'CLOSE_NOTIFICATION':
            var notifications = Object.assign({}, core.notifications);
            if (notifications[action.key]){
                notifications[action.key].closing = true;
            }
            return Object.assign({}, core, { notifications: notifications });
        case 'REMOVE_NOTIFICATION':
            var notifications = Object.assign({}, core.notifications);
            delete notifications[action.key];
            return Object.assign({}, core, {notifications: notifications});
        case 'GENERATE_SHARE_LINK':
            return Object.assign({}, core, {sharelink: action.sharelink})
        case 'GET_ROUTE_BY_COORDINATE':
            return Object.assign({}, core, {routeonrequest: action.routeonrequest})
        case 'INIT_CONFIGURATIONS':
            return Object.assign({}, core, {config: action.payload})
        case 'GET_SERVERINFO':
            return Object.assign({}, core, {serverinfo: action.payload})
        default:
            return core;
    }
}