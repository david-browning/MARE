using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml.Linq;

namespace InstallerUI.InstallerComponents
{
   public class ManifestParser
   {
      public ManifestParser(FileInfo docInfo, string copyToPath = null)
      {
         _doc = XDocument.Load(docInfo.OpenRead());
         if(copyToPath != null)
         {
            docInfo.CopyTo(copyToPath, true);
         }
      }

      public XElement LookupPackageXML(string packageId)
      {
         return _doc.Descendants(MANIFEST_NAMESPACE + "WixPackageProperties").Single(
            p => p.Attribute("Package").Value == packageId);
      }

      public string LookupPackageName(XElement element)
      {
         //Sometimes the manifest doesn't include this info.
         string ret = null; // element.Attribute("DisplayName").Value;
         return ret == null ? "" : ret;
      }

      public string LookupPackageDescription(XElement element)
      {
         //Sometimes the manifest doesn't include this info.
         string ret = null; // element.Attribute("Description").Value;
         return ret == null ? "" : ret;
      }

      public bool LookupPackageIsDependency(XElement element)
      {
         var value = element.Attribute("Permanent").Value;
         if(value.ToLower() == "yes")
         {
            return true;
         }

         return false;
      }

      public XElement LookupFeatureXML(string featureId)
      {
         return _doc.Descendants(MANIFEST_NAMESPACE + "WixPackageFeatureInfo").Single(
            f => f.Attribute("Feature").Value == featureId);
      }

      public string LookupFeatureName(XElement element)
      {
         return element.Attribute("Title").Value;
      }

      public string LookupFeatureDescription(XElement element)
      {
         return element.Attribute("Description").Value;
      }

      public int LookupFeatureAttributes(XElement element)
      {
         return Convert.ToInt32(element.Attribute("Attributes").Value);
      }

      private XDocument _doc;
      readonly XNamespace MANIFEST_NAMESPACE = "http://wixtoolset.org/schemas/v4/2010/BootstrapperApplicationData";

   }
}
