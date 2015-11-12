#include "strings.h"

const char* Strings::importString =  "import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEType;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEStruct;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEStructType;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVector;\n"
                            "import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVectorType;\n";

const char* Strings::defuzzificationStructString =
    "    // Struct able to save the centroid coordinate and the area. Used for defuzzication\n"
    "    private static final DFEStructType defuzzificationStruct = new DFEStructType(\n"
    "            new DFEStructType.StructFieldType(\"Area\", type),\n"
    "            new DFEStructType.StructFieldType(\"Centroid\", type));\n";

const char* Strings::triangleTypeString =
    "    // Define Vector to describe a triangle shaped fuzzy set\n"
    "    private static final DFEVectorType<DFEVar> triangleFuzzySetType =\n"
    "            new DFEVectorType<DFEVar>(type, 3);\n";

const char* Strings::triangleDataStructureCreationMethodeString =
    "    /**\n     * Function used to create a triangle shaped fuzzy set\n"
    "     * @param start start of the triangle\n"
    "     * @param peak peak of the triangle\n"
    "     * @param end end of the triangle\n"
    "     * @return a DFEVector containing all the parameters needed to describe the set\n"
    "     */\n"
    "    private DFEVector<DFEVar> createNewTriangleVector(double start, double peak, double end) {\n"
    "        // Create Vector\n"
    "        DFEVector<DFEVar> triangleVector = triangleFuzzySetType.newInstance(this);\n\n"
    "        // Set Values\n"
    "        triangleVector.connect(0, type.newInstance(this, start));\n"
    "        triangleVector.connect(1, type.newInstance(this, peak));\n"
    "        triangleVector.connect(2, type.newInstance(this, end));\n\n"
    "        return triangleVector;\n"
    "    }\n\n";

const char* Strings::triangleFuzzificationMethodeString =
    "    /**\n"
    "     * Function used to calculate the degree of membership of an given value into a triangle shaped fuzzy set\n"
    "     * @param triangleVector the vector describing the fuzzy set\n"
    "     * @param value actual value\n"
    "     * @return degree of membership\n"
    "     */\n"
    "    private DFEVar getFuzzificationTriangle(DFEVector<DFEVar> triangleVector, DFEVar value) {\n"
    "        DFEVar degreeOfMembership = constant.var(0);\n\n"
    "        degreeOfMembership = (value > triangleVector[0] & value <= triangleVector[1]) ?\n"
    "                (value - triangleVector[0]) / (triangleVector[1] - triangleVector[0]) :\n"
    "                degreeOfMembership;\n"
    "        degreeOfMembership = (value > triangleVector[1] & value < triangleVector[2]) ?\n"
    "                1 - (value - triangleVector[1]) / (triangleVector[2] - triangleVector[1]) :\n"
    "                degreeOfMembership;\n\n"
    "        return degreeOfMembership;\n"
    "    }\n\n";

const char* Strings::triangleDefuzzificationMethodeString =
    "    /**\n"
    "     * Function used for defuzzification of triangle shaped fuzzy sets\n"
    "     * @param triangleVector the vector describing the fuzzy set\n"
    "     * @param degreeOfMembership the degree of membership of the variable to the fuzzy set\n"
    "     * @return a struct containing information about the area and the centroid\n"
    "     */\n"
    "    private DFEStruct getDefuzzificationTriangle(DFEVector<DFEVar> triangleVector,\n"
    "            DFEVar degreeOfMembership) {\n"
    "        // creating struct to write to\n"
    "        DFEStruct information = defuzzificationStruct.newInstance(this);\n\n"
    "        // Calculate intersection of the 3 different parts of the trapezoid\n"
    "        DFEVar xCordLeft = triangleVector[0] + (triangleVector[1] -\n"
    "                triangleVector[0]) * degreeOfMembership;\n"
    "        DFEVar xCordRight = triangleVector[1] + (triangleVector[2] -\n"
    "                triangleVector[1]) * (1 - degreeOfMembership);\n\n"
    "        // Calculate length of border lines\n"
    "        DFEVar lengthTop = xCordRight - xCordLeft;\n"
    "        DFEVar lengthBottom = triangleVector[2] - triangleVector[0];\n\n"
    "        // Calculate Area\n"
    "        DFEVar area = (degreeOfMembership / 2) * (lengthTop + lengthBottom);\n"
    "        information.set(\"Area\", area);\n\n"
    "        // Calculate centroid\n"
    "        DFEVar centroid = (lengthBottom * lengthBottom - lengthTop * lengthTop +\n"
    "                (xCordRight - triangleVector[0]) * (lengthBottom + 2 * lengthTop)) /\n"
    "                (3 * (lengthBottom + lengthTop)) + triangleVector[0];\n"
    "        information.set(\"Centroid\", centroid);\n\n"
    "        return information;\n"
    "    }\n\n";
    
const char* Strings::managerImportString =
    "import com.maxeler.maxcompiler.v2.kernelcompiler.KernelConfiguration;\n"
    "import com.maxeler.maxcompiler.v2.kernelcompiler.KernelParameters;\n"
    "import com.maxeler.maxcompiler.v2.kernelcompiler._KernelConfiguration;\n"
    "import com.maxeler.maxcompiler.v2.managers.BuildConfig;\n"
    "import com.maxeler.maxcompiler.v2.managers.BuildConfig.Effort;\n"
    "import com.maxeler.maxcompiler.v2.managers.custom.CustomManager;\n"
    "import com.maxeler.maxcompiler.v2.managers.custom.DFELink;\n"
    "import com.maxeler.maxcompiler.v2.managers.custom.blocks.KernelBlock;\n"
    "import com.maxeler.maxcompiler.v2.managers.custom.stdlib.DebugLevel;\n"
    "import com.maxeler.maxcompiler.v2.managers.custom.stdlib.MemoryControllerConfig;\n"
    "import com.maxeler.maxcompiler.v2.managers.engine_interfaces.CPUTypes;\n"
    "import com.maxeler.maxcompiler.v2.managers.engine_interfaces.EngineInterface;\n"
    "import com.maxeler.maxcompiler.v2.managers.engine_interfaces.EngineInterface.Direction;\n"
    "import com.maxeler.maxcompiler.v2.managers.engine_interfaces.InterfaceParam;\n\n";

const char* Strings::managerString1 =
    "        super(params);\n\n"
    "        m_params = params;\n\n"
    "        setConfiguration();\n"
    "        addInterfaces();\n"
    "        setDesign();\n"
    "    }\n\n"
    "    private void setConfiguration() {\n"
    "        MemoryControllerConfig memConfig = new MemoryControllerConfig();\n"
    "        config.setMemoryControllerConfig(memConfig);\n\n"
    "        config.setDefaultStreamClockFrequency(m_params.getStreamFrequency());\n"
    "        if(m_params.getMemFrequency() > 0) config.setOnCardMemoryFrequency(m_params.getMemFrequency());\n"
    "        DebugLevel debugLevel = new DebugLevel();\n"
    "        debugLevel.setHasStreamStatus(m_params.getHasStreamStatus());\n"
    "        debug.setDebugLevel(debugLevel);\n\n"
    "        m_kernelConfig = getCurrentKernelConfig();\n"
    "        m_kernelConfig.optimization.setCEReplicationNumPartitions(m_params.getCEReplication());\n"
    "        m_kernelConfig.optimization.setUseGlobalClockBuffer(m_params.getIsBuffGce());\n"
    "        _KernelConfiguration.getPhotonKernelConfig(getCurrentKernelConfig()).optimizations().setMultiCycleResetEnabled(m_params.getIsMultiCycleReset());\n"
    "       _KernelConfiguration.getPhotonKernelConfig(getCurrentKernelConfig()).setClockPhasePartitioningEnabled(m_params.getIsPhaseClocks());\n"
    "    }\n\n"
    "    private EngineInterface createDefaultInterface() {\n"
    "        EngineInterface engine_interface = new EngineInterface(\"default\");\n\n"
    "        CPUTypes   type = CPUTypes.FLOAT;\n"
    "        int        size = type.sizeInBytes();\n"
    "        InterfaceParam  N    = engine_interface.addParam(\"N\", CPUTypes.INT);\n\n";

const char* Strings::managerString2 =
    "        engine_interface.ignoreAll(Direction.IN_OUT);\n"
    "        return engine_interface;\n"
    "    }\n\n"
    "    private void addInterfaces() {\n"
    "        createSLiCinterface(createDefaultInterface());\n"
    "    }\n\n"
    "    private void setDesign() {\n"
    "        KernelParameters kernelParams = makeKernelParameters(\n";

const char* Strings::managerString3 = 
    "        BuildConfig buildConfig = manager.getBuildConfig();\n"
    "        buildConfig.setBuildEffort(Effort.VERY_HIGH);\n"
    "        buildConfig.setEnableTimingAnalysis(true);\n"
    "        buildConfig.setMPPRCostTableSearchRange(params.getMPPRStartCT(), params.getMPPREndCT());\n"
    "        buildConfig.setMPPRParallelism(params.getMPPRThreads());\n"
    "        buildConfig.setMPPRRetryNearMissesThreshold(params.getMPPRRetryThreshold());\n\n"
    "        manager.build();\n"
    "    }\n"
    "}";

const char* Strings::engineParametersImportString =
    "import com.maxeler.maxcompiler.v2.build.EngineParameters;\n\n";

const char* Strings::engineParametersString1 =
    "    private static final String isBuffGce            = \"isBuffGce\";\n"
    "    private static final String isMultiCycleReset    = \"isMultiCycleReset\";\n"
    "    private static final String CEReplication        = \"CEReplication\";\n"
    "    private static final String maxFileName          = \"maxFileName\";\n"
    "    private static final String target               = \"target\";\n"
    "    private static final String MPPRRetryThreshold   = \"MPPRRetryThreshold\";\n"
    "    private static final String MPPRThreads          = \"MPPRThreads\";\n"
    "    private static final String streamFrequency      = \"streamFrequency\";\n"
    "    private static final String memFrequency         = \"memFrequency\";\n"
    "    private static final String numPipes             = \"numPipes\";\n"
    "    private static final String tag                  = \"tag\";\n"
    "    private static final String hasStreamStatus      = \"hasStreamStatus\";\n"
    "    private static final String isPhaseClocks        = \"isPhaseClocks\";\n"
    "    private static final String dspFactor            = \"dspFactor\";\n\n";

const char* Strings::engineParametersString2 =
    "        super(argv);\n"
    "    }\n\n"
    "    public boolean getIsBuffGce() {\n"
    "        return getParam(isBuffGce);\n"
    "    }\n\n"
    "    public boolean getIsMultiCycleReset() {\n"
    "        return getParam(isMultiCycleReset);\n"
    "    }\n\n"
    "    public int getCEReplication() {\n"
    "        return getParam(CEReplication);\n"
    "    }\n\n"
    "    public int getStreamFrequency() {\n"
    "        return getParam(streamFrequency);\n"
    "    }\n\n"
    "    public int getMemFrequency() {\n"
    "        return getParam(memFrequency);\n"
    "    }\n\n"
    "    public int getNumPipes() {\n"
    "        return getParam(numPipes);\n"
    "    }\n\n"
    "    public String getTag() {\n"
    "        return getParam(tag);\n"
    "    }\n\n"
    "    public boolean getHasStreamStatus() {\n"
    "        return getParam(hasStreamStatus);\n"
    "    }\n\n"
    "    public boolean getIsPhaseClocks() {\n"
    "        return getParam(isPhaseClocks);\n"
    "    }\n\n"
    "    public double getDspFactor() {\n"
    "        return getParam(dspFactor);\n"
    "    }\n\n"
    "    @Override\n"
    "    protected void declarations() {\n"
    "        /* Standard parameters */\n\n"
    "        // naming\n";

const char* Strings::engineParametersString3 =
    "        declareParam(tag, DataType.STRING, \"\");\n\n"
    "        // build parameters\n"
    "        declareParam(target, Target.class, Target.DFE);\n"
    "        declareParam(MPPRRetryThreshold, DataType.INT, 500);\n"
    "        declareParam(MPPRThreads, DataType.INT, 4);\n"
    "        declareParam(CEReplication, DataType.INT, 6);\n"
    "        declareParam(isBuffGce, DataType.BOOL, true);\n"
    "        declareParam(isMultiCycleReset, DataType.BOOL, true);\n"
    "        declareParam(isPhaseClocks, DataType.BOOL, false);\n\n"
    "        // common kernel parameters\n"
    "        declareParam(streamFrequency, DataType.INT, 150);\n"
    "        declareParam(memFrequency, DataType.INT, -1);\n"
    "        declareParam(numPipes, DataType.INT, 2);\n"
    "        declareParam(dspFactor, DataType.DOUBLE, 0.5);\n\n"
    "        // for debugging\n"
    "        declareParam(hasStreamStatus, DataType.BOOL, false);\n"
    "    }\n\n"
    "    @Override\n"
    "    protected void validate() {\n\n"
    "    }\n\n"
    "    @Override\n"
    "    public String getBuildName() {\n"
    "        return String.format(\"\%s_\%s_\%s\%s\",\n"
    "                getMaxFileName(), getDFEModel().toString(), getTarget().toString(),\n"
    "                getTag());\n"
    "    }\n\n"
    "}\n";

const char* Strings::cpuIncludeString =
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n\n"
    "#include \"MaxSLiCInterface.h\"\n"
    "#include \"Maxfiles.h\"\n\n";
