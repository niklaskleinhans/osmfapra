import React, { Component } from 'react';
import { bindActionCreators} from 'redux'
import { connect } from 'react-redux'

import Notifications from './components/Notifications'
import Home from './views/Home'

import * as mqttActions from './services/mqtt/actions'
import * as coreActions from './services/core/actions'

class App extends Component {

  constructor(props){
    super(props)
  }

  componentWillMount(){
    this.props.coreActions.initConfigurations(80,5000)
  }

  componentDidMount(){
    var actionTopicMapping = {};
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
    mqttActions: bindActionCreators(mqttActions, dispatch),
    coreActions: bindActionCreators(coreActions, dispatch)
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(App);