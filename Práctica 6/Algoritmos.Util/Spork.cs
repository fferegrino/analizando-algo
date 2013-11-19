using System;
using System.Collections.Generic;
using System.Net;
[assembly: CLSCompliant(true)]

namespace Algoritmos.Util.SporkRandom
{
    /// <summary>
    /// A .NET interface for random.org randomized number service. 
    /// More info on the service used at http://www.random.org/clients/http/
    /// Guidelines of use of the service at http://www.random.org/clients/
    /// </summary>
    public class Spork
    {
        RandomOrgAPI API;

        #region Constructor
        /// <summary>
        /// Constructs a spork.
        /// </summary>
        public Spork()
        {
            API = new RandomOrgAPI();
        }
        #endregion

        #region RandomInt
        #region Singular

        /// <summary>
        /// Retrieves a single random integer from random.org
        /// </summary>
        /// <param name="min">Minimum integer.</param>
        /// <param name="max">Maximum integer.</param>
        /// <returns>A random integer between the minimum and maximum.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public int RandomInt(int min, int max)
        {
            return Convert.ToInt32(API.DownloadHTML(API.GenerateIntegerURL(1, min, max)));
        }
        #endregion
        #region List

        /// <summary>
        /// Retrieves a list of integers from random.org
        /// </summary>
        /// <param name="min">Minimum integer.</param>
        /// <param name="max">Maximum integer.</param>
        /// <param name="listlength">Length of the list.</param>
        /// <returns>A list of integers between the specified maximum and minimum.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public List<int> RandomIntList(int min, int max, int listlength)
        {

            string html = API.DownloadHTML(API.GenerateIntegerURL(listlength, min, max));

            string[] arr = html.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);//Split for each line, removing empty lines

            List<int> listInt = new List<int>();
            foreach (string i in arr)
            {
                listInt.Add(Convert.ToInt32(i));
            }
            return listInt;
        }
        #endregion
        #endregion

        #region RandomString
        #region Singular

        /// <summary>
        /// Retrieves a random string from random.org
        /// </summary>
        /// <param name="stringlength">Amount of characters in the string.</param>
        /// <param name="options">The attributes of the random string, in StringOptions form.</param>
        /// <returns>A random string with the specified attributes.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public string RandomString(int stringlength, RandStringOptions options = RandStringOptions.All)
        {
            bool digits = false;
            bool upperAlpha = false;
            bool lowerAlpha = false;

            switch (options)
            {
                case RandStringOptions.Digits:
                    digits = true;
                    break;
                case RandStringOptions.UpperAlpha:
                    upperAlpha = true;
                    break;
                case RandStringOptions.LowerAlpha:
                    lowerAlpha = true;
                    break;
                case RandStringOptions.DigitsUpperAlpha:
                    digits = true;
                    upperAlpha = true;
                    break;
                case RandStringOptions.DigitsLowerAlpha:
                    digits = true;
                    lowerAlpha = true;
                    break;
                case RandStringOptions.LowerAlphaUpperAlpha:
                    lowerAlpha = true;
                    upperAlpha = true;
                    break;
                case RandStringOptions.All:
                    lowerAlpha = true;
                    upperAlpha = true;
                    digits = true;
                    break;
                default:
                    break;
            }
            string html = API.DownloadHTML(API.GenerateStringURL(1, stringlength, digits, upperAlpha, lowerAlpha));
            string[] arr = html.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            return arr[0];
        }
        #endregion
        #region List

        /// <summary>
        /// Retrieves a list of random strings from random.org
        /// </summary>
        /// <param name="stringlength">Length of the strings.</param>
        /// <param name="options">The attributes of the random strings, in StringOptions form.</param>
        /// <param name="listlength">The length of the list.</param>
        /// <returns>A list of randomized strings with the specified attributes.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public List<string> RandomStringList(int stringlength, int listlength, RandStringOptions options = RandStringOptions.All)
        {
            bool digits = true;
            bool upperAlpha = true;
            bool lowerAlpha = true;

            switch (options)
            {
                case RandStringOptions.Digits:
                    digits = true;
                    break;
                case RandStringOptions.UpperAlpha:
                    upperAlpha = true;
                    break;
                case RandStringOptions.LowerAlpha:
                    lowerAlpha = true;
                    break;
                case RandStringOptions.DigitsUpperAlpha:
                    digits = true;
                    upperAlpha = true;
                    break;
                case RandStringOptions.DigitsLowerAlpha:
                    digits = true;
                    lowerAlpha = true;
                    break;
                case RandStringOptions.LowerAlphaUpperAlpha:
                    lowerAlpha = true;
                    upperAlpha = true;
                    break;
                case RandStringOptions.All:
                    lowerAlpha = true;
                    upperAlpha = true;
                    digits = true;
                    break;
                default:
                    break;
            }



            string html = API.DownloadHTML(API.GenerateStringURL(listlength, stringlength, digits, upperAlpha, lowerAlpha));
            string[] arr = html.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);


            List<String> listString = new List<string>();
            foreach (string i in arr)
            {
                listString.Add(i);
            }
            return listString;

        }
        #endregion

        #endregion

        #region RandomBool
        #region Singular

        /// <summary>
        /// Retrieves a random boolean value from random.org
        /// </summary>
        /// <returns>A random boolean value.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public bool RandomBool()
        {
            return Convert.ToBoolean(RandomInt(0, 1));
        }
        #endregion
        #region List

        /// <summary>
        /// Retrieves a list of random boolean values from random.org
        /// </summary>
        /// <param name="listlength">The length of the list.</param>
        /// <returns>A list of random boolean values.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public List<bool> RandomBoolList(int listlength)
        {
            List<int> listInt = RandomIntList(0, 1, listlength);

            List<bool> listBool = new List<bool>();
            foreach (int i in listInt)
            {
                listBool.Add(Convert.ToBoolean(i));
            }
            return listBool;
        }
        #endregion
        #endregion

        #region RandomByte

        #region Singular
        /// <summary>
        /// Retrieves a random byte from random.org
        /// </summary>
        /// <returns>A random byte.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public byte RandomByte()
        {
            List<bool> boolList = RandomBoolList(8);

            bool[] boolArray = new bool[8];
            int i = 0;
            foreach (bool b in boolList)
            {
                boolArray[i] = b;
                i++;
            }

            byte[] byteArray = BoolArrayToByteArray(boolArray);
            return byteArray[0];

        }

        #endregion
        #region List
        /// <summary>
        /// Retrieves a list of random bytes from random.org
        /// </summary>
        /// <param name="listlength">The length of the list.</param>
        /// <returns>A list of random bytes.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public List<byte> RandomByteList(int listlength)
        {
            List<bool> boolList = RandomBoolList(listlength * 8);

            bool[] boolArray = new bool[listlength * 8];
            int i = 0;
            foreach (bool b in boolList)
            {
                boolArray[i] = b;
                i++;
            }

            byte[] byteArray = BoolArrayToByteArray(boolArray);

            List<byte> byteList = new List<byte>();
            i = 0;
            foreach (byte b in byteArray)
            {
                byteList.Add(byteArray[i]);
                i++;
            }
            return byteList;

        }
        #endregion
        #endregion


        #region GetQuota

        /// <summary>
        /// Retrieves the remaining quota of bits available from the client IP address.
        /// More info on the quota: http://www.random.org/clients/http/#quota
        /// </summary>
        /// <returns>An integer representing the total remaining bits.</returns>
        /// <exception cref="WebException">
        /// Thrown if daily download quota is depleted.
        /// </exception>
        public int GetRandomOrgQuota()
        {
            return API.GetQuota();
        }
        #endregion

        #region Utilities

        private byte[] BoolArrayToByteArray(bool[] input)//Code by Jon Skeet from a post on Stack Overflow
        {
            if (input.Length % 8 != 0)
            {
                throw new ArgumentException("input");
            }
            byte[] ret = new byte[input.Length / 8];
            for (int i = 0; i < input.Length; i += 8)
            {
                int value = 0;
                for (int j = 0; j < 8; j++)
                {
                    if (input[i + j])
                    {
                        value += 1 << (7 - j);
                    }
                }
                ret[i / 8] = (byte)value;
            }
            return ret;
        }
        #endregion


        #region RandomOrgAPI
        private class RandomOrgAPI
        {
            #region IntegerURL

            public string GenerateIntegerURL(int amount, int min, int max)
            {
                string url = "http://www.random.org/integers/?num=" + amount + "&min=" + min + "&max=" + max + "&col=1&base=10&format=plain&rnd=new";
                return url;
            }
            #endregion

            #region StringURL

            public string GenerateStringURL(int amount, int length, bool digits, bool upperAlpha, bool lowerAlpha)
            {


                string digitsStr = BoolToOnOff(digits);
                string upperAlphaStr = BoolToOnOff(upperAlpha);
                string lowerAlphaStr = BoolToOnOff(lowerAlpha);

                string url = "http://www.random.org/strings/?num=" + amount + "&len=" + length + "&digits=" + digitsStr + "&upperalpha=" + upperAlphaStr + "&loweralpha=" + lowerAlphaStr + "&unique=on&format=plain&rnd=new";
                return url;
            }
            #endregion

            #region DownloadHTML

            public string DownloadHTML(string url)
            {
                if (GetQuota() > 0)
                {
                    WebClient client = new WebClient();
                    string html = client.DownloadString(url);
                    if (SuccessfulQuery(html))//Check if the query resulted in an error or not
                    {
                        return html;
                    }
                    else
                    {
                        throw new WebException("Error occurred whilst querying random.org for random integer: " + html);
                    }
                }
                else
                {
                    throw new WebException("Random.org quota is lower than 0. (Currently " + GetQuota() + " bits) \n See http://www.random.org/clients/http/#quota for more details on the quota.");
                }

            }
            #endregion


            #region Utilities

            public bool SuccessfulQuery(string input)
            {
                if (input.Contains("Error:"))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }

            public int GetQuota()
            {
                WebClient client = new WebClient();
                string html = client.DownloadString("http://www.random.org/quota/?format=plain");
                if (SuccessfulQuery(html))
                {
                    return Convert.ToInt32(html);
                }
                else
                {
                    throw new WebException("Error occurred whilst querying random.org for quota: " + html);
                }

            }

            private string BoolToOnOff(bool input)
            {
                if (input)
                {
                    return "on";
                }
                else
                {
                    return "off";
                }
            }


            #endregion
        }
        #endregion
    }

    #region RandStringOptions

    /// <summary>
    /// Container for the string options available for the RandomString methods.
    /// </summary>
    public enum RandStringOptions
    {
        /// <summary>
        /// StringOptions for a string containing only random digits.
        /// </summary>
        Digits,
        /// <summary>
        /// StringOptions for a string containing only upper cased letters.
        /// </summary>
        UpperAlpha,
        /// <summary>
        /// StringOptions for a string containing only lower cased letters.
        /// </summary>
        LowerAlpha,
        /// <summary>
        /// StringOptions for a string containing only digits and uppercased letters.
        /// </summary>
        DigitsUpperAlpha,
        /// <summary>
        /// StringOptions for a string containing only digits and lowercased letters.
        /// </summary>
        DigitsLowerAlpha,
        /// <summary>
        /// StringOptions for a string containing only lower cased and upper cased letters.
        /// </summary>
        LowerAlphaUpperAlpha,
        /// <summary>
        /// StringOptions for a string containing digits, lower cased letters and upper cased letters.
        /// </summary>
        All
    }
    #endregion
}