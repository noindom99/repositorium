// -- FILE ------------------------------------------------------------------
// name       : RtfBraceNestingException.cs
// project    : RTF Framelet
// created    : Jani Giannoudis - 2009.02.19
// language   : c#
// environment: .NET 2.0
// copyright  : (c) 2004-2010 by Itenso GmbH, Switzerland
// --------------------------------------------------------------------------
using System;
using System.Runtime.Serialization;

namespace Itenso.Rtf
{

	// ------------------------------------------------------------------------
	/// <summary>Thrown upon RTF specific error conditions.</summary>
	[Serializable]
	public class RtfBraceNestingException : RtfStructureException
	{

		// ----------------------------------------------------------------------
		/// <summary>Creates a new instance.</summary>
		public RtfBraceNestingException()
		{
		} // RtfBraceNestingException

		// ----------------------------------------------------------------------
		/// <summary>Creates a new instance with the given message.</summary>
		/// <param name="message">the message to display</param>
		public RtfBraceNestingException(string message)
			: base(message)
		{
		} // RtfBraceNestingException

		// ----------------------------------------------------------------------
		/// <summary>Creates a new instance with the given message, based on the given cause.</summary>
		/// <param name="message">the message to display</param>
		/// <param name="cause">the original cause for this exception</param>
		public RtfBraceNestingException(string message, Exception cause)
			: base(message, cause)
		{
		} // RtfBraceNestingException

		// ----------------------------------------------------------------------
		/// <summary>Serialization support.</summary>
		/// <param name="info">the info to use for serialization</param>
		/// <param name="context">the context to use for serialization</param>
		protected RtfBraceNestingException(SerializationInfo info, StreamingContext context) :
			base(info, context)
		{
		} // RtfBraceNestingException

	} // class RtfBraceNestingException

} // namespace Itenso.Rtf
// -- EOF -------------------------------------------------------------------
