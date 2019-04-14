; rgba64_image_mark_RGBA64
+0x00	pushq               %rbp
+0x01	movq                %rsp, %rbp
+0x04	pushq               %r15
+0x06	pushq               %r14
+0x08	pushq               %r13
+0x0a	pushq               %r12
+0x0c	pushq               %rbx
+0x0d	subq                $216, %rsp
+0x14	xorl                %r10d, %r10d
+0x17	cmpq                %r10, 40(%rdi)
+0x1b	movl                %r9d, -152(%rbp)
+0x22	movl                %r8d, %ebx
+0x25	movl                $65535, %r9d
+0x2b	movl                $0, %r8d
+0x31	cmovel              %r9d, %r8d
+0x35	movq                24(%rsi), %r11
+0x39	movslq              %ebx, %rax
+0x3c	subq                %rax, %r11
+0x3f	movq                %r11, -216(%rbp)
+0x46	movl                8(%rdi), %eax
+0x49	shrl                $22, %eax
+0x4c	imull               256(%rdi), %eax
+0x53	movslq              %edx, %r14
+0x56	shlq                $4, %r14
+0x5a	shrl                $3, %eax
+0x5d	movl                260(%rdi), %r11d
+0x64	addl                $-1, %r11d
+0x68	imull               24(%rdi), %r11d
+0x6d	movq                32(%rdi), %rdx
+0x71	movq                %rdx, -96(%rbp)
+0x75	addq                %rdx, %r11
+0x78	addq                %rax, %r11
+0x7b	movq                72(%rsi), %rdx
+0x7f	movslq              %ecx, %rcx
+0x82	movq                %rdx, -208(%rbp)
+0x89	imulq               %rdx, %rcx
+0x8d	addq                40(%rsi), %rcx
+0x91	movq                %rcx, %rdx
+0x94	movq                %rdi, -176(%rbp)
+0x9b	cmpq                %r10, 176(%rdi)
+0xa2	movw                8(%rsi), %r15w
+0xa7	movl                (%rsi), %ecx
+0xa9	movl                %ecx, -148(%rbp)
+0xaf	movq                16(%rsi), %rcx
+0xb3	movq                %rcx, -56(%rbp)
+0xb7	movq                128(%rsi), %r10
+0xbe	movq                120(%rsi), %rdi
+0xc2	movq                56(%rsi), %r13
+0xc6	movq                %rbx, -128(%rbp)
+0xca	movl                %r15d, -44(%rbp)
+0xce	movq                %rdi, -168(%rbp)
+0xd5	movq                %r13, -104(%rbp)
+0xd9	je                  "rgba64_image_mark_RGBA64+0x944"
+0xdf	movq                88(%rsi), %rcx
+0xe3	movq                %rcx, -256(%rbp)
+0xea	movq                104(%rsi), %rcx
+0xee	movq                %rcx, -248(%rbp)
+0xf5	movl                $1, %ecx
+0xfa	shlxq               %r13, %rcx, %rcx
+0xff	addq                $-1, %rcx
+0x103	movq                %rcx, -240(%rbp)
+0x10a	leaq                -4(%r13), %rcx
+0x10e	movq                %rcx, -232(%rbp)
+0x115	negq                %rdi
+0x118	movq                %rdi, -224(%rbp)
+0x11f	addq                $-8, %r11
+0x123	shlq                $48, %r8
+0x127	movq                %r8, -80(%rbp)
+0x12b	andnl               %r9d, %r15d, %ecx
+0x130	movl                %ecx, -160(%rbp)
+0x136	leal                -1(%rbx), %ecx
+0x139	addq                $1, %rcx
+0x13d	movq                %rcx, -200(%rbp)
+0x144	movl                %ebx, %ecx
+0x146	movq                %rcx, -192(%rbp)
+0x14d	leaq                8(%r10,%r14), %rax
+0x152	movq                %rax, -184(%rbp)
+0x159	leaq                4127484(%rip), %r8
+0x160	movq                %r11, -72(%rbp)
+0x164	movq                %rdx, %rax
+0x167	movq                -96(%rbp), %rsi
+0x16b	    sarxq               %r13, %rax, %rdi
+0x170	    movq                %rax, %rdx
+0x173	    movq                -248(%rbp), %rax
+0x17a	    subq                %rdx, %rax
+0x17d	    movq                %rdx, %rcx
+0x180	    subq                -256(%rbp), %rcx
+0x187	    orq                 %rax, %rcx
+0x18a	    movq                %rdx, -120(%rbp)
+0x18e	    js                  "rgba64_image_mark_RGBA64+0x1d6"
+0x190	    movq                %rdx, %rax
+0x193	    andq                -240(%rbp), %rax
+0x19a	    movq                -232(%rbp), %rcx
+0x1a1	    sarxq               %rcx, %rax, %rax
+0x1a6	    andl                $15, %eax
+0x1a9	    leaq                4127356(%rip), %rcx
+0x1b0	    movb                (%rax,%rcx), %cl
+0x1b3	    cmpq                $7, %rax
+0x1b7	    movq                -168(%rbp), %rax
+0x1be	    movq                %rax, %rdx
+0x1c1	    cmovbq              -224(%rbp), %rdx
+0x1c9	    movq                %rdx, -112(%rbp)
+0x1cd	    andb                $15, %cl
+0x1d0	    movq                %rcx, -88(%rbp)
+0x1d4	    jmp                 "rgba64_image_mark_RGBA64+0x1e9"
+0x1d6	    xorl                %eax, %eax
+0x1d8	    movq                %rax, -88(%rbp)
+0x1dc	    xorl                %eax, %eax
+0x1de	    movq                %rax, -112(%rbp)
+0x1e2	    movq                -168(%rbp), %rax
+0x1e9	    imulq               %rax, %rdi
+0x1ed	    movq                -176(%rbp), %rax
+0x1f4	    addq                32(%rax), %rdi
+0x1f8	    movq                %rdi, -144(%rbp)
+0x1ff	    cmpl                $1, -148(%rbp)
+0x206	    jne                 "rgba64_image_mark_RGBA64+0x571"
+0x20c	    testl               %ebx, %ebx
+0x20e	    movq                -56(%rbp), %rax
+0x212	    jle                 "rgba64_image_mark_RGBA64+0x915"
+0x218	    movzbl              -88(%rbp), %ecx
+0x21c	    movq                %rcx, -136(%rbp)
+0x223	    movq                -192(%rbp), %rcx
+0x22a	    movq                %rcx, %r9
+0x22d	    movq                -184(%rbp), %r11
+0x234	    movq                %rax, %r10
+0x237	        movq                %r9, -64(%rbp)
+0x23b	        movq                (%r11), %r13
+0x23e	        movq                -8(%r11), %rax
+0x242	        addq                -144(%rbp), %rax
+0x249	        movq                -72(%rbp), %r9
+0x24d	        cmpq                %rax, %r9
+0x250	        movq                %rax, %rcx
+0x253	        cmovbq              %r9, %rcx
+0x257	        cmpq                %rsi, %rcx
+0x25a	        cmovbq              %rsi, %rcx
+0x25e	        movbew              6(%rcx), %dx
+0x264	        movbew              (%rcx), %di
+0x269	        movbew              2(%rcx), %bx
+0x26f	        movbew              4(%rcx), %cx
+0x275	        movzwl              %dx, %edx
+0x278	        shlq                $48, %rdx
+0x27c	        movzwl              %cx, %ecx
+0x27f	        shlq                $32, %rcx
+0x283	        movzwl              %bx, %ebx
+0x286	        shlq                $16, %rbx
+0x28a	        movzwl              %di, %r12d
+0x28e	        orq                 %rdx, %r12
+0x291	        orq                 %rbx, %r12
+0x294	        orq                 %rcx, %r12
+0x297	        movl                %r13d, %r14d
+0x29a	        andb                $15, %r14b
+0x29e	        je                  "rgba64_image_mark_RGBA64+0x411"
+0x2a4	        sarq                $4, %r13
+0x2a8	        leaq                (%rax,%r13), %rcx
+0x2ac	        cmpq                %rcx, %r9
+0x2af	        cmovbq              %r9, %rcx
+0x2b3	        cmpq                %rsi, %rcx
+0x2b6	        cmovbq              %rsi, %rcx
+0x2ba	        movbew              6(%rcx), %dx
+0x2c0	        movbew              (%rcx), %r15w
+0x2c6	        movbew              2(%rcx), %bx
+0x2cc	        movbew              4(%rcx), %cx
+0x2d2	        movzwl              %dx, %edx
+0x2d5	        shlq                $48, %rdx
+0x2d9	        movq                %rsi, %rdi
+0x2dc	        movzwl              %cx, %esi
+0x2df	        shlq                $32, %rsi
+0x2e3	        movzwl              %bx, %ebx
+0x2e6	        shlq                $16, %rbx
+0x2ea	        movzwl              %r15w, %ecx
+0x2ee	        orq                 %rdx, %rcx
+0x2f1	        orq                 %rbx, %rcx
+0x2f4	        orq                 %rsi, %rcx
+0x2f7	        cmpb                $0, -88(%rbp)
+0x2fb	        je                  "rgba64_image_mark_RGBA64+0x3de"
+0x301	        addq                -112(%rbp), %rax
+0x305	        cmpq                %rax, %r9
+0x308	        movq                %rax, %rdx
+0x30b	        cmovbq              %r9, %rdx
+0x30f	        cmpq                %rdi, %rdx
+0x312	        cmovbq              %rdi, %rdx
+0x316	        movbew              6(%rdx), %si
+0x31c	        movbew              (%rdx), %r15w
+0x322	        movbew              2(%rdx), %bx
+0x328	        movbew              4(%rdx), %dx
+0x32e	        movzwl              %si, %esi
+0x331	        shlq                $48, %rsi
+0x335	        movzwl              %dx, %r8d
+0x339	        shlq                $32, %r8
+0x33d	        movzwl              %bx, %ebx
+0x340	        shlq                $16, %rbx
+0x344	        movzwl              %r15w, %edx
+0x348	        orq                 %rsi, %rdx
+0x34b	        orq                 %rbx, %rdx
+0x34e	        orq                 %r8, %rdx
+0x351	        addq                %r13, %rax
+0x354	        cmpq                %rax, %r9
+0x357	        cmovbq              %r9, %rax
+0x35b	        cmpq                %rdi, %rax
+0x35e	        cmovbq              %rdi, %rax
+0x362	        movbew              6(%rax), %si
+0x368	        movbew              (%rax), %r8w
+0x36e	        movbew              2(%rax), %bx
+0x374	        movbew              4(%rax), %ax
+0x37a	        movzwl              %si, %esi
+0x37d	        shlq                $48, %rsi
+0x381	        movzwl              %ax, %r15d
+0x385	        shlq                $32, %r15
+0x389	        movzwl              %bx, %ebx
+0x38c	        shlq                $16, %rbx
+0x390	        movzwl              %r8w, %eax
+0x394	        leaq                4126913(%rip), %r8
+0x39b	        orq                 %rsi, %rax
+0x39e	        orq                 %rbx, %rax
+0x3a1	        orq                 %r15, %rax
+0x3a4	        movq                -136(%rbp), %rdi
+0x3ab	        movq                (%r8,%rdi,8), %rsi
+0x3af	        movq                %rsi, %rbx
+0x3b2	        andq                %rsi, %rdx
+0x3b5	        andq                %rsi, %rax
+0x3b8	        andq                %r12, %rsi
+0x3bb	        shrxq               %rdi, %rsi, %rsi
+0x3c0	        subq                %rsi, %r12
+0x3c3	        andq                %rcx, %rbx
+0x3c6	        shrxq               %rdi, %rbx, %rsi
+0x3cb	        subq                %rsi, %rcx
+0x3ce	        shrxq               %rdi, %rdx, %rdx
+0x3d3	        addq                %rdx, %r12
+0x3d6	        shrxq               %rdi, %rax, %rax
+0x3db	        addq                %rax, %rcx
+0x3de	        movl                -44(%rbp), %r15d
+0x3e2	        movq                -104(%rbp), %r13
+0x3e6	        movq                -64(%rbp), %r9
+0x3ea	        movzbl              %r14b, %eax
+0x3ee	        movq                (%r8,%rax,8), %rdx
+0x3f2	        andq                %rdx, %rcx
+0x3f5	        andq                %r12, %rdx
+0x3f8	        shrxq               %rax, %rdx, %rdx
+0x3fd	        subq                %rdx, %r12
+0x400	        shrxq               %rax, %rcx, %rax
+0x405	        addq                %rax, %r12
+0x408	        movq                -80(%rbp), %rdx
+0x40c	        jmp                 "rgba64_image_mark_RGBA64+0x492"
+0x411	        cmpb                $0, -88(%rbp)
+0x415	        je                  "rgba64_image_mark_RGBA64+0x486"
+0x417	        addq                -112(%rbp), %rax
+0x41b	        movq                -72(%rbp), %rcx
+0x41f	        cmpq                %rax, %rcx
+0x422	        cmovbq              %rcx, %rax
+0x426	        cmpq                %rsi, %rax
+0x429	        cmovbq              %rsi, %rax
+0x42d	        movbew              6(%rax), %cx
+0x433	        movbew              (%rax), %dx
+0x438	        movbew              2(%rax), %si
+0x43e	        movbew              4(%rax), %ax
+0x444	        movzwl              %cx, %ecx
+0x447	        shlq                $48, %rcx
+0x44b	        movzwl              %ax, %eax
+0x44e	        shlq                $32, %rax
+0x452	        movzwl              %si, %esi
+0x455	        shlq                $16, %rsi
+0x459	        movzwl              %dx, %edx
+0x45c	        orq                 %rcx, %rdx
+0x45f	        orq                 %rsi, %rdx
+0x462	        orq                 %rax, %rdx
+0x465	        movq                -136(%rbp), %rcx
+0x46c	        movq                (%r8,%rcx,8), %rax
+0x470	        andq                %rax, %rdx
+0x473	        andq                %r12, %rax
+0x476	        shrxq               %rcx, %rax, %rax
+0x47b	        subq                %rax, %r12
+0x47e	        shrxq               %rcx, %rdx, %rax
+0x483	        addq                %rax, %r12
+0x486	        movq                -104(%rbp), %r13
+0x48a	        movq                -80(%rbp), %rdx
+0x48e	        movq                -64(%rbp), %r9
+0x492	        movzwl              %r15w, %ecx
+0x496	        movq                %r12, %rax
+0x499	        orq                 %rdx, %rax
+0x49c	        cmpl                $65535, %ecx
+0x4a2	        je                  "rgba64_image_mark_RGBA64+0x53c"
+0x4a8	        movzwl              %r12w, %ecx
+0x4ac	        movq                %r12, %r14
+0x4af	        shrq                $16, %r14
+0x4b3	        movzwl              %r14w, %ebx
+0x4b7	        movq                %r12, %r8
+0x4ba	        movl                -160(%rbp), %esi
+0x4c0	        imull               %esi, %ecx
+0x4c3	        shrq                $32, %r8
+0x4c7	        imull               %esi, %ebx
+0x4ca	        movzwl              %r8w, %edx
+0x4ce	        imull               %esi, %edx
+0x4d1	        shrq                $48, %rax
+0x4d5	        movl                %eax, %edi
+0x4d7	        imull               %esi, %edi
+0x4da	        movl                %ecx, %esi
+0x4dc	        shrl                $16, %esi
+0x4df	        leal                1(%rcx,%rsi), %ecx
+0x4e3	        movl                %ebx, %esi
+0x4e5	        shrl                $16, %esi
+0x4e8	        leal                1(%rbx,%rsi), %esi
+0x4ec	        movl                %edx, %ebx
+0x4ee	        shrl                $16, %ebx
+0x4f1	        leal                1(%rdx,%rbx), %edx
+0x4f5	        movl                %edi, %ebx
+0x4f7	        shrl                $16, %ebx
+0x4fa	        leal                1(%rdi,%rbx), %edi
+0x4fe	        shrl                $16, %ecx
+0x501	        shrl                $16, %esi
+0x504	        shrl                $16, %edx
+0x507	        shrl                $16, %edi
+0x50a	        subl                %ecx, %r12d
+0x50d	        subl                %esi, %r14d
+0x510	        subl                %edx, %r8d
+0x513	        subl                %edi, %eax
+0x515	        shlq                $48, %rax
+0x519	        movzwl              %r8w, %ecx
+0x51d	        leaq                4126520(%rip), %r8
+0x524	        shlq                $32, %rcx
+0x528	        shll                $16, %r14d
+0x52c	        movzwl              %r12w, %edx
+0x530	        orq                 %rax, %rdx
+0x533	        orq                 %r14, %rdx
+0x536	        orq                 %rcx, %rdx
+0x539	        movq                %rdx, %rax
+0x53c	        movq                -96(%rbp), %rsi
+0x540	        movq                %rax, (%r10)
+0x543	        addq                $8, %r10
+0x547	        addq                $16, %r11
+0x54b	        addq                $-1, %r9
+0x54f	        jne                 "rgba64_image_mark_RGBA64+0x237"
+0x555	    movq                -56(%rbp), %rcx
+0x559	    movq                -200(%rbp), %rax
+0x560	    leaq                (%rcx,%rax,8), %rcx
+0x564	    movq                -128(%rbp), %rbx
+0x568	    movq                -72(%rbp), %r11
+0x56c	    jmp                 "rgba64_image_mark_RGBA64+0x918"
+0x571	    testl               %ebx, %ebx
+0x573	    movq                -56(%rbp), %rax
+0x577	    jle                 "rgba64_image_mark_RGBA64+0x915"
+0x57d	    movzbl              -88(%rbp), %ecx
+0x581	    movq                %rcx, -136(%rbp)
+0x588	    movq                -192(%rbp), %rcx
+0x58f	    movq                %rcx, %r13
+0x592	    movq                -184(%rbp), %r14
+0x599	    movq                %rax, %r15
+0x59c	        movq                %r13, -64(%rbp)
+0x5a0	        movq                (%r14), %r8
+0x5a3	        movq                -8(%r14), %rdx
+0x5a7	        addq                -144(%rbp), %rdx
+0x5ae	        cmpq                %rdx, %r11
+0x5b1	        movq                %rdx, %rax
+0x5b4	        cmovbq              %r11, %rax
+0x5b8	        cmpq                %rsi, %rax
+0x5bb	        cmovbq              %rsi, %rax
+0x5bf	        movbew              6(%rax), %cx
+0x5c5	        movq                %rsi, %r13
+0x5c8	        movbew              (%rax), %si
+0x5cd	        movbew              2(%rax), %bx
+0x5d3	        movbew              4(%rax), %ax
+0x5d9	        movzwl              %cx, %ecx
+0x5dc	        shlq                $48, %rcx
+0x5e0	        movzwl              %ax, %edi
+0x5e3	        shlq                $32, %rdi
+0x5e7	        movzwl              %bx, %ebx
+0x5ea	        shlq                $16, %rbx
+0x5ee	        movzwl              %si, %r12d
+0x5f2	        orq                 %rcx, %r12
+0x5f5	        orq                 %rbx, %r12
+0x5f8	        orq                 %rdi, %r12
+0x5fb	        movl                %r8d, %r9d
+0x5fe	        andb                $15, %r9b
+0x602	        je                  "rgba64_image_mark_RGBA64+0x74b"
+0x608	        sarq                $4, %r8
+0x60c	        leaq                (%rdx,%r8), %rsi
+0x610	        cmpq                %rsi, %r11
+0x613	        cmovbq              %r11, %rsi
+0x617	        cmpq                %r13, %rsi
+0x61a	        cmovbq              %r13, %rsi
+0x61e	        movbew              6(%rsi), %di
+0x624	        movbew              (%rsi), %r10w
+0x62a	        movbew              2(%rsi), %cx
+0x630	        movbew              4(%rsi), %si
+0x636	        movzwl              %di, %edi
+0x639	        shlq                $48, %rdi
+0x63d	        movzwl              %si, %ebx
+0x640	        shlq                $32, %rbx
+0x644	        movzwl              %cx, %ecx
+0x647	        shlq                $16, %rcx
+0x64b	        movzwl              %r10w, %esi
+0x64f	        orq                 %rdi, %rsi
+0x652	        orq                 %rcx, %rsi
+0x655	        orq                 %rbx, %rsi
+0x658	        cmpb                $0, -88(%rbp)
+0x65c	        je                  "rgba64_image_mark_RGBA64+0x7d1"
+0x662	        addq                -112(%rbp), %rdx
+0x666	        cmpq                %rdx, %r11
+0x669	        movq                %rdx, %rcx
+0x66c	        cmovbq              %r11, %rcx
+0x670	        cmpq                %r13, %rcx
+0x673	        cmovbq              %r13, %rcx
+0x677	        movbew              6(%rcx), %di
+0x67d	        movbew              (%rcx), %r10w
+0x683	        movbew              2(%rcx), %bx
+0x689	        movbew              4(%rcx), %cx
+0x68f	        movzwl              %di, %edi
+0x692	        shlq                $48, %rdi
+0x696	        movzwl              %cx, %r11d
+0x69a	        shlq                $32, %r11
+0x69e	        movzwl              %bx, %ecx
+0x6a1	        shlq                $16, %rcx
+0x6a5	        movzwl              %r10w, %ebx
+0x6a9	        orq                 %rdi, %rbx
+0x6ac	        orq                 %rcx, %rbx
+0x6af	        orq                 %r11, %rbx
+0x6b2	        movq                -72(%rbp), %r11
+0x6b6	        addq                %r8, %rdx
+0x6b9	        cmpq                %rdx, %r11
+0x6bc	        cmovbq              %r11, %rdx
+0x6c0	        cmpq                %r13, %rdx
+0x6c3	        cmovbq              %r13, %rdx
+0x6c7	        movbew              6(%rdx), %cx
+0x6cd	        movbew              (%rdx), %r8w
+0x6d3	        movbew              2(%rdx), %di
+0x6d9	        movbew              4(%rdx), %dx
+0x6df	        movzwl              %cx, %r10d
+0x6e3	        shlq                $48, %r10
+0x6e7	        movzwl              %dx, %edx
+0x6ea	        shlq                $32, %rdx
+0x6ee	        movzwl              %di, %edi
+0x6f1	        shlq                $16, %rdi
+0x6f5	        movzwl              %r8w, %ecx
+0x6f9	        orq                 %r10, %rcx
+0x6fc	        orq                 %rdi, %rcx
+0x6ff	        orq                 %rdx, %rcx
+0x702	        leaq                4126035(%rip), %rax
+0x709	        movq                %rax, %r8
+0x70c	        movq                -136(%rbp), %rax
+0x713	        movq                (%r8,%rax,8), %rdx
+0x717	        movq                %rdx, %rdi
+0x71a	        andq                %rdx, %rbx
+0x71d	        andq                %rdx, %rcx
+0x720	        andq                %r12, %rdx
+0x723	        shrxq               %rax, %rdx, %rdx
+0x728	        subq                %rdx, %r12
+0x72b	        andq                %rsi, %rdi
+0x72e	        shrxq               %rax, %rdi, %rdx
+0x733	        subq                %rdx, %rsi
+0x736	        shrxq               %rax, %rbx, %rdx
+0x73b	        addq                %rdx, %r12
+0x73e	        shrxq               %rax, %rcx, %rcx
+0x743	        addq                %rcx, %rsi
+0x746	        jmp                 "rgba64_image_mark_RGBA64+0x7db"
+0x74b	        cmpb                $0, -88(%rbp)
+0x74f	        je                  "rgba64_image_mark_RGBA64+0x7c7"
+0x751	        addq                -112(%rbp), %rdx
+0x755	        cmpq                %rdx, %r11
+0x758	        cmovbq              %r11, %rdx
+0x75c	        movq                -96(%rbp), %rax
+0x760	        cmpq                %rax, %rdx
+0x763	        cmovbq              %rax, %rdx
+0x767	        movbew              6(%rdx), %cx
+0x76d	        movbew              (%rdx), %si
+0x772	        movbew              2(%rdx), %di
+0x778	        movbew              4(%rdx), %dx
+0x77e	        movzwl              %cx, %ecx
+0x781	        shlq                $48, %rcx
+0x785	        movzwl              %dx, %edx
+0x788	        shlq                $32, %rdx
+0x78c	        movzwl              %di, %edi
+0x78f	        shlq                $16, %rdi
+0x793	        movzwl              %si, %esi
+0x796	        orq                 %rcx, %rsi
+0x799	        orq                 %rdi, %rsi
+0x79c	        orq                 %rdx, %rsi
+0x79f	        leaq                4125878(%rip), %rax
+0x7a6	        movq                -136(%rbp), %rdx
+0x7ad	        movq                (%rax,%rdx,8), %rcx
+0x7b1	        andq                %rcx, %rsi
+0x7b4	        andq                %r12, %rcx
+0x7b7	        shrxq               %rdx, %rcx, %rcx
+0x7bc	        subq                %rcx, %r12
+0x7bf	        shrxq               %rdx, %rsi, %rcx
+0x7c4	        addq                %rcx, %r12
+0x7c7	        movq                -80(%rbp), %rax
+0x7cb	        movq                -64(%rbp), %r13
+0x7cf	        jmp                 "rgba64_image_mark_RGBA64+0x801"
+0x7d1	        leaq                4125828(%rip), %rax
+0x7d8	        movq                %rax, %r8
+0x7db	        movq                -64(%rbp), %r13
+0x7df	        movzbl              %r9b, %ecx
+0x7e3	        movq                (%r8,%rcx,8), %rdx
+0x7e7	        andq                %rdx, %rsi
+0x7ea	        andq                %r12, %rdx
+0x7ed	        shrxq               %rcx, %rdx, %rdx
+0x7f2	        subq                %rdx, %r12
+0x7f5	        shrxq               %rcx, %rsi, %rcx
+0x7fa	        addq                %rcx, %r12
+0x7fd	        movq                -80(%rbp), %rax
+0x801	        movzwl              -44(%rbp), %ecx
+0x805	        movq                %r12, %rsi
+0x808	        orq                 %rax, %rsi
+0x80b	        cmpl                $65535, %ecx
+0x811	        je                  "rgba64_image_mark_RGBA64+0x8a6"
+0x817	        movzwl              %r12w, %edx
+0x81b	        movq                %r12, %r9
+0x81e	        shrq                $16, %r9
+0x822	        movzwl              %r9w, %ebx
+0x826	        movq                %r12, %r8
+0x829	        movl                -160(%rbp), %edi
+0x82f	        imull               %edi, %edx
+0x832	        shrq                $32, %r8
+0x836	        imull               %edi, %ebx
+0x839	        movzwl              %r8w, %ecx
+0x83d	        imull               %edi, %ecx
+0x840	        shrq                $48, %rsi
+0x844	        movl                %esi, %eax
+0x846	        imull               %edi, %eax
+0x849	        movl                %edx, %edi
+0x84b	        shrl                $16, %edi
+0x84e	        leal                1(%rdx,%rdi), %r10d
+0x853	        movl                %ebx, %edi
+0x855	        shrl                $16, %edi
+0x858	        leal                1(%rbx,%rdi), %edi
+0x85c	        movl                %ecx, %edx
+0x85e	        shrl                $16, %edx
+0x861	        leal                1(%rcx,%rdx), %ecx
+0x865	        movl                %eax, %edx
+0x867	        shrl                $16, %edx
+0x86a	        leal                1(%rax,%rdx), %eax
+0x86e	        shrl                $16, %r10d
+0x872	        shrl                $16, %edi
+0x875	        shrl                $16, %ecx
+0x878	        shrl                $16, %eax
+0x87b	        subl                %r10d, %r12d
+0x87e	        subl                %edi, %r9d
+0x881	        subl                %ecx, %r8d
+0x884	        subl                %eax, %esi
+0x886	        shlq                $48, %rsi
+0x88a	        movzwl              %r8w, %eax
+0x88e	        shlq                $32, %rax
+0x892	        shll                $16, %r9d
+0x896	        movzwl              %r12w, %ecx
+0x89a	        orq                 %rsi, %rcx
+0x89d	        orq                 %r9, %rcx
+0x8a0	        orq                 %rax, %rcx
+0x8a3	        movq                %rcx, %rsi
+0x8a6	        movq                %rsi, %rax
+0x8a9	        shrq                $48, %rax
+0x8ad	        testw               %ax, %ax
+0x8b0	        je                  "rgba64_image_mark_RGBA64+0x8db"
+0x8b2	        movzwl              %ax, %ecx
+0x8b5	        cmpl                $65535, %ecx
+0x8bb	        jne                 "rgba64_image_mark_RGBA64+0x8c2"
+0x8bd	        movq                %rsi, (%r15)
+0x8c0	        jmp                 "rgba64_image_mark_RGBA64+0x8db"
+0x8c2	        movq                (%r15), %rdx
+0x8c5	        movl                $65535, %ecx
+0x8ca	        andnl               %ecx, %eax, %ecx
+0x8cf	        movq                %r15, %rdi
+0x8d2	        callq               "rgba64_DplusDM"
+0x8d7	        movq                -72(%rbp), %r11
+0x8db	        addq                $8, %r15
+0x8df	        addq                $16, %r14
+0x8e3	        addq                $-1, %r13
+0x8e7	        movq                -96(%rbp), %rsi
+0x8eb	        jne                 "rgba64_image_mark_RGBA64+0x59c"
+0x8f1	    movq                -56(%rbp), %rcx
+0x8f5	    movq                -200(%rbp), %rax
+0x8fc	    leaq                (%rcx,%rax,8), %rcx
+0x900	    movq                -128(%rbp), %rbx
+0x904	    movl                -44(%rbp), %r15d
+0x908	    movq                -104(%rbp), %r13
+0x90c	    leaq                4125513(%rip), %r8
+0x913	    jmp                 "rgba64_image_mark_RGBA64+0x918"
+0x915	    movq                %rax, %rcx
+0x918	    movq                -216(%rbp), %rax
+0x91f	    leaq                (%rcx,%rax,8), %rcx
+0x923	    movq                %rcx, -56(%rbp)
+0x927	    movq                -120(%rbp), %rax
+0x92b	    addq                -208(%rbp), %rax
+0x932	    addl                $-1, -152(%rbp)
+0x939	    jne                 "rgba64_image_mark_RGBA64+0x16b"
+0x93f	jmp                 "rgba64_image_mark_RGBA64+0xc90"
+0x944	addq                %r14, %r10
+0x947	addq                $-8, %r11
+0x94b	movl                %r8d, %eax
+0x94e	movq                %rax, -88(%rbp)
+0x952	andnl               %r9d, %r15d, %eax
+0x957	movl                %eax, -144(%rbp)
+0x95d	leal                -1(%rbx), %eax
+0x960	addq                $1, %rax
+0x964	movq                %rax, -64(%rbp)
+0x968	movl                %ebx, %eax
+0x96a	movq                %rax, -160(%rbp)
+0x971	leaq                -1(%rax), %rax
+0x975	movq                %rax, -112(%rbp)
+0x979	movq                %r11, -72(%rbp)
+0x97d	movq                %rdx, %rcx
+0x980	movq                -96(%rbp), %rdx
+0x984	movq                %r10, -80(%rbp)
+0x988	jmp                 "rgba64_image_mark_RGBA64+0x9b2"
+0x98a	    addq                -208(%rbp), %rax
+0x991	    movq                %rax, %rcx
+0x994	    movq                -216(%rbp), %rax
+0x99b	    movq                -56(%rbp), %rdx
+0x99f	    leaq                (%rdx,%rax,8), %rdx
+0x9a3	    movq                %rdx, -56(%rbp)
+0x9a7	    movq                -176(%rbp), %rax
+0x9ae	    movq                32(%rax), %rdx
+0x9b2	    sarxq               %r13, %rcx, %rax
+0x9b7	    imulq               -168(%rbp), %rax
+0x9bf	    addq                %rdx, %rax
+0x9c2	    movq                %rax, -96(%rbp)
+0x9c6	    cmpl                $1, -148(%rbp)
+0x9cd	    movq                %rcx, %rax
+0x9d0	    movq                %rax, -120(%rbp)
+0x9d4	    jne                 "rgba64_image_mark_RGBA64+0xb18"
+0x9da	    testl               %ebx, %ebx
+0x9dc	    jle                 "rgba64_image_mark_RGBA64+0xc83"
+0x9e2	    movq                -160(%rbp), %r13
+0x9e9	    movq                %r10, %r11
+0x9ec	    movq                -56(%rbp), %r14
+0x9f0	        movzwl              %r15w, %r10d
+0x9f4	        movq                (%r11), %rax
+0x9f7	        addq                -96(%rbp), %rax
+0x9fb	        movq                -72(%rbp), %rcx
+0x9ff	        cmpq                %rax, %rcx
+0xa02	        cmovbq              %rcx, %rax
+0xa06	        cmpq                %rdx, %rax
+0xa09	        movq                %rdx, %r8
+0xa0c	        cmovbq              %rdx, %rax
+0xa10	        movbew              6(%rax), %si
+0xa16	        movbew              (%rax), %bx
+0xa1b	        movbew              2(%rax), %di
+0xa21	        movbew              4(%rax), %ax
+0xa27	        movzwl              %si, %esi
+0xa2a	        movzwl              %ax, %r15d
+0xa2e	        movzwl              %di, %r12d
+0xa32	        movzwl              %bx, %r9d
+0xa36	        orq                 -88(%rbp), %rsi
+0xa3a	        cmpl                $65535, %r10d
+0xa41	        je                  "rgba64_image_mark_RGBA64+0xabe"
+0xa43	        movl                %r9d, %ecx
+0xa46	        movl                -144(%rbp), %edi
+0xa4c	        imull               %edi, %ecx
+0xa4f	        movl                %r12d, %edx
+0xa52	        imull               %edi, %edx
+0xa55	        movl                %r15d, %eax
+0xa58	        imull               %edi, %eax
+0xa5b	        movl                %esi, %r10d
+0xa5e	        imull               %edi, %r10d
+0xa62	        movl                %ecx, %ebx
+0xa64	        shrl                $16, %ebx
+0xa67	        leal                1(%rcx,%rbx), %ecx
+0xa6b	        movl                %edx, %edi
+0xa6d	        shrl                $16, %edi
+0xa70	        leal                1(%rdx,%rdi), %edx
+0xa74	        movl                %eax, %edi
+0xa76	        shrl                $16, %edi
+0xa79	        leal                1(%rax,%rdi), %eax
+0xa7d	        movl                %r10d, %edi
+0xa80	        shrl                $16, %edi
+0xa83	        leal                1(%r10,%rdi), %edi
+0xa88	        shrl                $16, %ecx
+0xa8b	        shrl                $16, %edx
+0xa8e	        shrl                $16, %eax
+0xa91	        shrl                $16, %edi
+0xa94	        subl                %ecx, %r9d
+0xa97	        subl                %edx, %r12d
+0xa9a	        subl                %eax, %r15d
+0xa9d	        subl                %edi, %esi
+0xa9f	        shlq                $48, %rsi
+0xaa3	        movzwl              %r15w, %eax
+0xaa7	        shlq                $32, %rax
+0xaab	        shll                $16, %r12d
+0xaaf	        movzwl              %r9w, %ecx
+0xab3	        orl                 %r12d, %ecx
+0xab6	        orq                 %rax, %rcx
+0xab9	        orq                 %rcx, %rsi
+0xabc	        jmp                 "rgba64_image_mark_RGBA64+0xad3"
+0xabe	        shlq                $32, %r15
+0xac2	        shlq                $16, %r12
+0xac6	        shlq                $48, %rsi
+0xaca	        orq                 %r9, %rsi
+0xacd	        orq                 %r12, %rsi
+0xad0	        orq                 %r15, %rsi
+0xad3	        movq                -120(%rbp), %rax
+0xad7	        movl                -44(%rbp), %r15d
+0xadb	        movq                %rsi, (%r14)
+0xade	        addq                $8, %r14
+0xae2	        addq                $16, %r11
+0xae6	        addq                $-1, %r13
+0xaea	        movq                %r8, %rdx
+0xaed	        jne                 "rgba64_image_mark_RGBA64+0x9f0"
+0xaf3	    movq                -56(%rbp), %rcx
+0xaf7	    movq                -64(%rbp), %rdx
+0xafb	    leaq                (%rcx,%rdx,8), %rcx
+0xaff	    movq                %rcx, -56(%rbp)
+0xb03	    movq                -72(%rbp), %r11
+0xb07	    movq                -104(%rbp), %r13
+0xb0b	    movq                -80(%rbp), %r10
+0xb0f	    movq                -128(%rbp), %rbx
+0xb13	    jmp                 "rgba64_image_mark_RGBA64+0xc83"
+0xb18	    movl                $65535, %r12d
+0xb1e	    movq                -112(%rbp), %r13
+0xb22	    movq                %r10, %r14
+0xb25	    movq                -56(%rbp), %r15
+0xb29	    testl               %ebx, %ebx
+0xb2b	    jg                  "rgba64_image_mark_RGBA64+0xb49"
+0xb2d	    jmp                 "rgba64_image_mark_RGBA64+0xc6f"
+0xb32	        addq                $8, %r15
+0xb36	        movq                -176(%rbp), %rax
+0xb3d	        movq                32(%rax), %rdx
+0xb41	        addq                $16, %r14
+0xb45	        addq                $-1, %r13
+0xb49	        movzwl              -44(%rbp), %r8d
+0xb4e	        movq                (%r14), %rax
+0xb51	        addq                -96(%rbp), %rax
+0xb55	        cmpq                %rax, %r11
+0xb58	        cmovbq              %r11, %rax
+0xb5c	        cmpq                %rdx, %rax
+0xb5f	        cmovbq              %rdx, %rax
+0xb63	        movbew              6(%rax), %cx
+0xb69	        movbew              (%rax), %bx
+0xb6e	        movbew              2(%rax), %di
+0xb74	        movbew              4(%rax), %ax
+0xb7a	        movzwl              %cx, %esi
+0xb7d	        movzwl              %ax, %r9d
+0xb81	        movzwl              %di, %r11d
+0xb85	        movzwl              %bx, %r10d
+0xb89	        orq                 -88(%rbp), %rsi
+0xb8d	        cmpl                $65535, %r8d
+0xb94	        je                  "rgba64_image_mark_RGBA64+0xc0d"
+0xb96	        movl                %r10d, %ecx
+0xb99	        movl                -144(%rbp), %edi
+0xb9f	        imull               %edi, %ecx
+0xba2	        movl                %r11d, %eax
+0xba5	        imull               %edi, %eax
+0xba8	        movl                %r9d, %edx
+0xbab	        imull               %edi, %edx
+0xbae	        movl                %esi, %ebx
+0xbb0	        imull               %edi, %ebx
+0xbb3	        movl                %ecx, %edi
+0xbb5	        shrl                $16, %edi
+0xbb8	        leal                1(%rcx,%rdi), %ecx
+0xbbc	        movl                %eax, %edi
+0xbbe	        shrl                $16, %edi
+0xbc1	        leal                1(%rax,%rdi), %eax
+0xbc5	        movl                %edx, %edi
+0xbc7	        shrl                $16, %edi
+0xbca	        leal                1(%rdx,%rdi), %edx
+0xbce	        movl                %ebx, %edi
+0xbd0	        shrl                $16, %edi
+0xbd3	        leal                1(%rbx,%rdi), %edi
+0xbd7	        shrl                $16, %ecx
+0xbda	        shrl                $16, %eax
+0xbdd	        shrl                $16, %edx
+0xbe0	        shrl                $16, %edi
+0xbe3	        subl                %ecx, %r10d
+0xbe6	        subl                %eax, %r11d
+0xbe9	        subl                %edx, %r9d
+0xbec	        subl                %edi, %esi
+0xbee	        shlq                $48, %rsi
+0xbf2	        movzwl              %r9w, %eax
+0xbf6	        shlq                $32, %rax
+0xbfa	        shll                $16, %r11d
+0xbfe	        movzwl              %r10w, %ecx
+0xc02	        orl                 %r11d, %ecx
+0xc05	        orq                 %rax, %rcx
+0xc08	        orq                 %rcx, %rsi
+0xc0b	        jmp                 "rgba64_image_mark_RGBA64+0xc22"
+0xc0d	        shlq                $32, %r9
+0xc11	        shlq                $16, %r11
+0xc15	        shlq                $48, %rsi
+0xc19	        orq                 %r10, %rsi
+0xc1c	        orq                 %r11, %rsi
+0xc1f	        orq                 %r9, %rsi
+0xc22	        movq                -72(%rbp), %r11
+0xc26	        movq                %rsi, %rax
+0xc29	        shrq                $48, %rax
+0xc2d	        testw               %ax, %ax
+0xc30	        je                  "rgba64_image_mark_RGBA64+0xc56"
+0xc32	        movzwl              %ax, %ecx
+0xc35	        cmpl                $65535, %ecx
+0xc3b	        jne                 "rgba64_image_mark_RGBA64+0xc42"
+0xc3d	        movq                %rsi, (%r15)
+0xc40	        jmp                 "rgba64_image_mark_RGBA64+0xc56"
+0xc42	        movq                (%r15), %rdx
+0xc45	        andnl               %r12d, %eax, %ecx
+0xc4a	        movq                %r15, %rdi
+0xc4d	        callq               "rgba64_DplusDM"
+0xc52	        movq                -72(%rbp), %r11
+0xc56	        testq               %r13, %r13
+0xc59	        jne                 "rgba64_image_mark_RGBA64+0xb32"
+0xc5f	    movq                -56(%rbp), %rax
+0xc63	    movq                -64(%rbp), %rcx
+0xc67	    leaq                (%rax,%rcx,8), %rax
+0xc6b	    movq                %rax, -56(%rbp)
+0xc6f	    movq                -128(%rbp), %rbx
+0xc73	    movq                -120(%rbp), %rax
+0xc77	    movl                -44(%rbp), %r15d
+0xc7b	    movq                -104(%rbp), %r13
+0xc7f	    movq                -80(%rbp), %r10
+0xc83	    addl                $-1, -152(%rbp)
+0xc8a	    jne                 "rgba64_image_mark_RGBA64+0x98a"
+0xc90	addq                $216, %rsp
+0xc97	popq                %rbx
+0xc98	popq                %r12
+0xc9a	popq                %r13
+0xc9c	popq                %r14
+0xc9e	popq                %r15
+0xca0	popq                %rbp
+0xca1	retq
