import React from 'react';
import { connect } from 'react-redux';

function MyComponent({ dispatch }) {
  return (
    <button onClick={() => dispatch({ type: 'INCREMENT' })}>
      Increment
    </button>
  );
}

export default connect()(MyComponent);
