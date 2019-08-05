import React, { Component } from 'react';
import { bindActionCreators} from 'redux'
import { connect } from 'react-redux'

import Notifications from './components/Notifications'
import Home from './views/Home'

import * as mqttActions from './services/mqtt/actions'

class App extends Component {

  constructor(props){
    super(props)
  }

  componentDidMount(){
    var actionTopicMapping = {
        'RECEIVE_COORDINATES': 'client/coordinates/1234'
    };
    this.props.mqttActions.initMqttConnection(actionTopicMapping)
  }


  render() {
    var className = "App";
    return (
      <div className={className}>
        <div className="body">
          <Home/>
          <Notifications/>
        </div>
      </div>
    );
  }
}

const mapStateToProps = (state, ownProps) => {
  return{}
}

const mapDispatchToProps = (dispatch) => {
  return {
    mqttActions: bindActionCreators(mqttActions, dispatch)
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(App);