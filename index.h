const char PAGE_INDEX[] PROGMEM = R"=====(
<!doctype html>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>雲朵光線</title>
    <link href="https://code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css" rel="stylesheet" type="text/css">
    <style type="text/css">
        body {
            font-family: "微軟正黑體", "黑體-繁", sans-serif;
        }
        #slider {
            width: 300px;
            margin: 15px;
        }
    </style>
</head>

<body>
    <h1>請選擇亮度</h1>
    <br>
    雲亮度：
    <div id="LED_Dimm">
        <input type="radio" id="LED_100" class="SW" value="100" name="SW">
        <label for="LED_100"> 100% </label>
        <input type="radio" id="LED_75" class="SW" value="75" name="SW">
        <label for="LED_75"> 75% </label>
    <input type="radio" id="LED_50" class="SW"  value="50" name="SW">
        <label for="LED_50"> 50% </label>
    <input type="radio" id="LED_25" class="SW" value="25" name="SW">
        <label for="LED_25"> 25% </label>
    <input type="radio" id="LED_0" class="SW" value="0" name="SW">
        <label for="LED_0"> 0% </label>
    </div>
  倒數時間：
    <div id="LED_time">
      <input type="radio" id="LED_T1H" class="TM" value="60" name="SW">
        <label for="LED_T1H"> 1hr </label>
        <input type="radio" id="LED_T30M" class="TM" value="30" name="SW">
        <label for="LED_T30M"> 30min </label>
        <input type="radio" id="LED_T10M" class="TM" value="10" name="SW">
        <label for="LED_T10M"> 10min </label>
        <input type="radio" id="LED_T5M" class="TM  " value="5" name="SW">
        <label for="LED_T5M"> 5min </label> 
    </div>
    <script src="https://code.jquery.com/jquery-1.12.1.min.js"></script>
    <script src="https://code.jquery.com/ui/1.11.4/jquery-ui.min.js"></script>
  
    <script>
  
        $(function () {
            $("#LED_Dimm").buttonset();
            $(".SW").change(function (evt) {
                var state = $(this).val();
                $.post("/DIMM", { dimm: state });
            });
        });
    
        $(function () {
            $("#LED_time").buttonset();
            $(".TM").change(function (evt) {
                var state = $(this).val();
                $.post("/TIME", { timevalue: state });
            });
        }); 
    
    
    </script>
  
</body>

</html>
)=====";
