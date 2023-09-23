from selenium import webdriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
import time
import json

# Main Function
if __name__ == "__main__":
  
    # Enable Performance Logging of Chrome.
    desired_capabilities = DesiredCapabilities.CHROME
    desired_capabilities["goog:loggingPrefs"] = {"performance": "ALL"}
  
    # Create the webdriver object and pass the arguments
    options = webdriver.ChromeOptions()
  
    # Chrome will start in Headless mode
    options.add_argument('headless')
  
    # Ignores any certificate errors if there is any
    options.add_argument("--ignore-certificate-errors")
  
    # Startup the chrome webdriver with executable path and
    # pass the chrome options and desired capabilities as
    # parameters.
    driver = webdriver.Chrome(#executable_path="C:/Users/user/Desktop/chromedriver.exe",
                              options=options,
                              #desired_capabilities=desired_capabilities
                              )
  
    # Send a request to the website and let it load
    driver.get("https://cool.ntu.edu.tw/courses/31890/modules/items/1229587")
  
    # Sleeps for 10 seconds
    time.sleep(10)
  
    # Gets all the logs from performance in Chrome
    logs = driver.get_log("performance")
  
    # Opens a writable JSON file and writes the logs in it
    with open("network_log.json", "w", encoding="utf-8") as f:
        f.write("[")
  
        # Iterates every logs and parses it using JSON
        for log in logs:
            network_log = json.loads(log["message"])["message"]
  
            # Checks if the current 'method' key has any
            # Network related value.
            if("Network.response" in network_log["method"]
                    or "Network.request" in network_log["method"]
                    or "Network.webSocket" in network_log["method"]):
  
                # Writes the network log to a JSON file by
                # converting the dictionary to a JSON string
                # using json.dumps().
                f.write(json.dumps(network_log)+",")
        f.write("{}]")
  
    print("Quitting Selenium WebDriver")
    driver.quit()
  
    # Read the JSON File and parse it using
    # json.loads() to find the urls containing images.
    json_file_path = "network_log.json"
    with open(json_file_path, "r", encoding="utf-8") as f:
        logs = json.loads(f.read())
  
    # Iterate the logs
    for log in logs:
  
        # Except block will be accessed if any of the
        # following keys are missing.
        try:
            # URL is present inside the following keys
            url = log["params"]["request"]["url"]
  
            # Checks if the extension is .png or .jpg
            if url[len(url)-4:] == ".png" or url[len(url)-4:] == ".jpg":
                print(url, end='\n\n')
        except Exception as e:
            pass