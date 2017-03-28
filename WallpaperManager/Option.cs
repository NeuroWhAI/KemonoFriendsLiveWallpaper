using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace WallpaperManager
{
    public class Option
    {
        public Option()
        {

        }

        //###########################################################################################

        public List<int> ScreenNumbers
        { get; set; } = new List<int>();

        public bool AutoRun
        { get; set; } = false;

        //###########################################################################################

        public void SaveToFile(string fileName)
        {
            using (var sw = new StreamWriter(new FileStream(fileName, FileMode.Create)))
            {
                sw.WriteLine(this.ScreenNumbers.Count);

                foreach (int idx in this.ScreenNumbers)
                {
                    sw.WriteLine(idx);
                }

                sw.WriteLine(this.AutoRun ? 'y' : 'n');
            }
        }

        public void LoadFromFile(string fileName)
        {
            try
            {
                this.ScreenNumbers.Clear();

                using (var sr = new StreamReader(new FileStream(fileName, FileMode.Open)))
                {
                    int length = int.Parse(sr.ReadLine());

                    for (int i = 0; i < length; ++i)
                    {
                        int idx = int.Parse(sr.ReadLine());
                        this.ScreenNumbers.Add(idx);
                    }

                    this.AutoRun = (sr.ReadLine() == "y");
                }
            }
            catch (FileNotFoundException)
            {

            }
            catch (EndOfStreamException)
            {

            }
            catch (FormatException)
            {

            }
        }
    }
}
