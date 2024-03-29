﻿// -- FILE ------------------------------------------------------------------
// name       : RtfXmlConvertSettings.cs
// project    : RTF Framelet
// created    : Jani Giannoudis - 2008.06.10
// language   : c#
// environment: .NET 2.0
// copyright  : (c) 2004-2010 by Itenso GmbH, Switzerland
// --------------------------------------------------------------------------

namespace Itenso.Rtf.Converter.Xml
{

	// ------------------------------------------------------------------------
	public class RtfXmlConvertSettings
	{

		// ----------------------------------------------------------------------
		public RtfXmlConvertSettings()
			: this(null, null)
		{
		} // RtfXmlConvertSettings

		// ----------------------------------------------------------------------
		public RtfXmlConvertSettings(string ns)
			: this(null, ns)
		{
		} // RtfXmlConvertSettings

		// ----------------------------------------------------------------------
		public RtfXmlConvertSettings(string prefix, string ns)
		{
			this.prefix = prefix;
			this.ns = ns;
		} // RtfXmlConvertSettings

		// ----------------------------------------------------------------------
		public string Prefix
		{
			get { return prefix; }
			set { prefix = value; }
		} // Prefix

		// ----------------------------------------------------------------------
		public string Ns
		{
			get { return ns; }
			set { ns = value; }
		} // Ns

		// ----------------------------------------------------------------------
		public bool IsShowHiddenText
		{
			get { return showHiddenText; }
			set { showHiddenText = value; }
		} // IsShowHiddenText

		// ----------------------------------------------------------------------
		// members
		private string prefix;
		private string ns;
		private bool showHiddenText;

	} // class RtfXmlConvertSettings

} // namespace Itenso.Rtf.Converter.Xml
// -- EOF -------------------------------------------------------------------
