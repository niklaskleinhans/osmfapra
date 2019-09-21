
import React, { PropTypes } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import { faHashtag, faStopwatch, faTimes } from '@fortawesome/free-solid-svg-icons'

import List from '@material-ui/core/List';
import ListItem from '@material-ui/core/ListItem';
import Divider from '@material-ui/core/Divider';
import ListItemText from '@material-ui/core/ListItemText';
import ListItemAvatar from '@material-ui/core/ListItemAvatar';

import * as coreActions from '../services/core/actions'


class Serverinfo extends React.Component{

    constructor(props){
        super(props);
    }


    calculateImportTime(){
        var timeInSeconds = this.props.serverinfo.importtime/1000000
        var minutes = Math.floor(timeInSeconds / 60)
        var seconds = (timeInSeconds- (minutes*60))
        return minutes + " m " + seconds.toFixed(2) + " s"
    }

    render(){
        return(
            <div>

            {this.props.serverinfo_open ?
                <div className="fullscreen"> 
                    <div className="blurbackground"/>
                    <div className="infocontainer">
                            <a onClick={e => this.props.coreActions.toggleServerinfo()}>
                                <FontAwesomeIcon icon={faTimes} size="2x"></FontAwesomeIcon>
                            </a>
                            <List className="materiallist">
                                <Divider variant="inset" />
                                <ListItem alignItems="flex-start">
                                    <ListItemAvatar>
                                        <FontAwesomeIcon icon={faHashtag} size="2x"></FontAwesomeIcon>
                                    </ListItemAvatar>
                                    <ListItemText
                                        primary="Nodecount"
                                        secondary={this.props.serverinfo.nodecount}
                                    />
                                </ListItem>
                                <Divider variant="inset" component="li" />
                                <ListItem alignItems="flex-start">
                                    <ListItemAvatar>
                                        <FontAwesomeIcon icon={faHashtag} size="2x"></FontAwesomeIcon>
                                    </ListItemAvatar>
                                    <ListItemText
                                        primary="Edgecount"
                                        secondary={this.props.serverinfo.edgecount}
                                    />
                                </ListItem>
                                <Divider variant="inset" component="li" />
                                <ListItem alignItems="flex-start">
                                    <ListItemAvatar>
                                        <FontAwesomeIcon icon={faStopwatch} size="2x"></FontAwesomeIcon>
                                    </ListItemAvatar>
                                    <ListItemText
                                        primary="Time needed for import"
                                        secondary={this.calculateImportTime()}
                                    />
                                </ListItem>

                            </List>
                    </div>
                </div> : null}
            </div>
        )
    }
}


/**
 * Export our component
 *
 * We also integrate our global store, using connect()
 **/

const mapStateToProps = (state, ownProps) => {
    return {
        serverinfo_open : state.core.serverinfo_open,
        serverinfo : state.core.serverinfo,
    }
};

const mapDispatchToProps = (dispatch) => {
    return {
        coreActions: bindActionCreators(coreActions, dispatch)
    }
};

// We wrap our Sidebar with the Router, and then to the redux store
export default connect(mapStateToProps, mapDispatchToProps)(Serverinfo)