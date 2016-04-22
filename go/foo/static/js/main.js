
  function postValue () {
    var build=$("#build");
    var nodes=$("#nodes");
    var node_array = nodes.val().split(',');
    var node_length = node_array.length;
    
    var object = {};
    object['url'] = build.val();
    object['nodes'] = [];
    
    for (var index = 0; index < node_length; index++) {
      object['nodes'].push(node_array[index]);
    }

    var json = JSON.stringify(object);

    $.post("foo", json,
           function(data, status) {
           alert("Status: " + status);
           });

    //alert(json);
  }

  function browseLink () {
    var url = "http://10.218.2.40/builds/main/";
    window.open(url, "Suman", "width=500, height=500");
  }
  
  function submit () {
    var update=$("#update");
    var browse=$("#browse");
    update.on( "click", postValue);
    browse.on( "click", browseLink);
  }
