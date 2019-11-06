#ifndef PP_DDEX_SCHEMA_H_
#define PP_DDEX_SCHEMA_H_

#include <vector>
#include <map>

static std::map<std::string,std::map<std::string,std::vector<std::string>>> schema = {
  { "301", {
    { "MusicalWorkLicenseInformationMessage", {
      "MessageHeader",
      "LicensedRelease"
    } },
    { "NewDealMessage", {
      "MessageHeader",
      "ReleaseDeal"
    } },
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "WorkList",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Release",
      "ReleaseDeal"
    } }
  } },
  { "312", {
    { "MusicalWorkLicenseInformationMessage", {
      "MessageHeader",
      "LicensedRelease"
    } },
    { "NewDealMessage", {
      "MessageHeader",
      "ReleaseDeal"
    } },
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } }
  } },
  { "32", {
    { "MusicalWorkLicenseInformationMessage", {
      "MessageHeader",
      "LicensedRelease"
    } },
    { "NewDealMessage", {
      "MessageHeader",
      "ReleaseDeal"
    } },
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } }
  } },
  { "33", {
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } },
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "CatalogTransfer",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } }
  } },
  { "34", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "CatalogTransfer",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "341", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "CatalogTransfer",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "35", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "351", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "WorkList",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "36", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "37", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "371", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "37D1", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "37D2", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } }
  } },
  { "38", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } },
    { "PurgeReleaseMessage", {
      "MessageHeader",
      "PurgedRelease"
    } }
  } },
  { "381", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } },
    { "PurgeReleaseMessage", {
      "MessageHeader",
      "PurgedRelease"
    } }
  } },
  { "382", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "UpdateIndicator",
      "IsBackfill",
      "CatalogTransfer",
      "MusicalWork",
      "CueSheet",
      "SoundRecording",
      "MIDI",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "UserDefinedResource",
      "Collection",
      "Release",
      "ReleaseDeal"
    } },
    { "CatalogListMessage", {
      "MessageHeader",
      "PublicationDate",
      "CatalogItem"
    } },
    { "PurgeReleaseMessage", {
      "MessageHeader",
      "PurgedRelease"
    } }
  } },
  { "40", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "Party",
      "CueSheetList",
      "SoundRecording",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "Chapter",
      "Release",
      "TrackRelease",
      "ReleaseDeal"
    } },
    { "PurgeReleaseMessage", {
      "MessageHeader",
      "PurgedRelease"
    } }
  } },
  { "41", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "Party",
      "CueSheetList",
      "SoundRecording",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "Chapter",
      "Release",
      "TrackRelease",
      "ReleaseDeal",
      "SupplementalDocument"
    } },
    { "PurgeReleaseMessage", {
      "MessageHeader",
      "PurgedRelease"
    } }
  } },
  { "411", {
    { "NewReleaseMessage", {
      "MessageHeader",
      "Party",
      "CueSheetList",
      "SoundRecording",
      "Video",
      "Image",
      "Text",
      "SheetMusic",
      "Software",
      "Chapter",
      "Release",
      "TrackRelease",
      "ReleaseDeal",
      "SupplementalDocument"
    } },
    { "PurgeReleaseMessage", {
      "MessageHeader",
      "PurgedRelease"
    } }
  } }
};


static std::map<std::string,std::string> types = {
  { "AllDealsCancelled", "Bool"},
  { "TakeDown", "Bool"},
  { "IsExclusive", "Bool"},
  { "IsArtistRelated", "Bool"},
  { "IsMedley", "Bool"},
  { "IsPotpourri", "Bool"},
  { "IsInstrumental", "Bool"},
  { "IsBackground", "Bool"},
  { "IsHiddenResource", "Bool"},
  { "IsBonusResource", "Bool"},
  { "IsComputerGenerated", "Bool"},
  { "NoSilenceBefore", "Bool"},
  { "NoSilenceAfter", "Bool"},
  { "Duration", "Duration"},
  { "SequenceNumber", "Int"},
  { "StartPoint", "Double"},
  { "EndPoint", "Double"},
  { "TopLeftCorner", "Double"},
  { "BottomRightCorner", "Double"},
  { "EffectiveDate", "String"},
  { "SequenceSubNumber", "Int"},
  { "AspectRatio", "Double"},
  { "ColorDepth", "Int"},
  { "ImageResolution", "Int"},
  { "IsPreview", "Bool"},
  { "NumberOfVoices", "Int"},
  { "NumberOfChannels", "Int"},
  { "BitsPerSample", "Int"},
  { "NumberOfAudioChannels", "Int"},
  { "AudioBitsPerSample", "Int"},
  { "IsComplete", "Bool"},
  { "DurationOfMusicalContent", "Duration"},
  { "IsDance", "Bool"},
  { "HasMusicalContent", "Bool"},
  { "StartTime", "String"},
  { "EndTime", "String"},
  { "IsPromotional", "Bool"},
  { "PromotionalCode", "Bool"},
  { "NumberOfProductsPerCarton", "Int"},
  { "PhysicalReturnsAllowed", "Bool"},
  { "LatestDateForPhysicalReturns", "String"},
  { "NumberOfUnitsPerPhysicalRelease", "Int"},
  { "CatalogTransferCompleted", "Bool"},
  { "Value", "Double"},
  { "PerformerInformationRequired", "Bool"},
  { "ResourceProcessingRequired", "Bool"},
  { "UsableResourceDuration", "Duration"},
  { "AccessBlockingRequested", "Bool"},
  { "EmbeddingAllowed", "Bool"},
  { "UserRatingAllowed", "Bool"},
  { "UserCommentAllowed", "Bool"},
  { "UserResponsesAllowed", "Bool"},
  { "ReportUsageRequested", "Bool"},
  { "PublicationDate", "String"},
  { "IsMultiArtistCompilation", "Bool"},
  { "SyndicationAllowed", "Bool"},
  { "IsBackfill", "Bool"},
  { "IsFeaturedArtist", "Bool"},
  { "IsContractedArtist", "Bool"},
  { "RightShareUnknown", "Bool"},
  { "RightSharePercentage", "Double"},
  { "StartDate", "String"},
  { "EndDate", "String"},
  { "IsRemastered", "Bool"},
  { "NumberOfFeaturedArtists", "Int"},
  { "NumberOfNonFeaturedArtists", "Int"},
  { "NumberOfContractedArtists", "Int"},
  { "NumberOfNonContractedArtists", "Int"},
  { "ReleaseDisplayStartDate", "String"},
  { "TrackListingPreviewStartDate", "String"},
  { "CoverArtPreviewStartDate", "String"},
  { "ClipPreviewStartDate", "String"},
  { "HasPreOrderFulfillment", "Bool"},
  { "Year", "Int"},
  { "InclusionDate", "String"},
  { "NumberOfCollections", "Int"},
  { "FulfillmentDate", "String"},
  { "DateTime", "String"},
  { "MessageCreatedDateTime", "String"},
  { "DurationUsed", "Duration"},
  { "IsInstantGratificationResource", "Bool"},
  { "IsFragment", "Bool"},
  { "HasFirstLicenseRefusal", "Bool"},
  { "NumberOfUsages", "Int"},
  { "IsPreOrderDeal", "Bool"},
  { "IsPreOrderIncentiveResource", "Bool"},
  { "ReleaseDisplayStartDateTime", "String"},
  { "TrackListingPreviewStartDateTime", "String"},
  { "CoverArtPreviewStartDateTime", "String"},
  { "ClipPreviewStartDateTime", "String"},
  { "PreOrderPreviewDateTime", "String"},
  { "IsCommunicatedOutOfBand", "Bool"},
  { "ContainsHiddenContent", "Bool"},
  { "IsCompilation", "Bool"},
  { "IsSoundtrack", "Bool"},
  { "IsHiResMusic", "Bool"},
  { "BitDepth", "Int"},
  { "FileSize", "Double"},
  { "Percentage", "Double"},
  { "HasMadeFeaturedContribution", "Bool"},
  { "HasMadeContractedContribution", "Bool"},
  { "NoDisplaySequence", "Bool"},
  { "PercentageOfRightsAssignment", "Double"},
  { "IsDisplayedInTitle", "Bool"},
  { "IsCover", "Bool"},
  { "SamplingRate", "Double"},
  { "WholesalePricePerUnit", "Double" }
};

#endif