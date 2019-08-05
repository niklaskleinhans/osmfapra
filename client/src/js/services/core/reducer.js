export default function reducer(core = {}, action){
    switch(action.type){
        case 'SET_NAME':
            return Object.assign({}, core, {name: action.payload});
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
        default:
            return core;
    }
}