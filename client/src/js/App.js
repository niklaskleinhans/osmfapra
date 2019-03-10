import React, { Component } from 'react';
import { bindActionCreators} from 'redux'
import { connect } from 'react-redux'

import Home from './views/Home'

class App extends Component {
  render() {
    var className = "App";
    return (
      <div className={className}>
        <div className="body">
          <Home/>
        </div>
      </div>
    );
  }
}

const mapStateToProps = (state, ownProps) => {
  return{}
}

const mapDispatchToProps = (dispatch) => {
  return {}
}

export default connect(mapStateToProps, mapDispatchToProps)(App);